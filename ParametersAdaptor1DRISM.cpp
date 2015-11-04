#include "ParametersAdaptor1DRISM.h"

#include "SimpleMatrix.h"
#include "PairParameter.h"
#include "StringParameter.h"
#include "DoubleParameter.h"

#include <stdlib.h>

#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

  int m_nsites;
   Real *m_densities;
   Matrix<Real> *m_distMatrix;
   const char **m_siteNames;

   Real *m_sigma, *m_epsilon, *m_charge;



inline bool check_type(Parameter *p,const char T)
{
	return  (T=='s' && p->getType() == Parameter::STRING )
	     || (T=='n' && p->getType() == Parameter::DOUBLE )
             || (T=='p' && p->getType() == Parameter::PAIR)
             || (T=='a' && p->getType() == Parameter::ARRAY );  
}

inline const char *type_to_name(const char t)
{
 	if(t=='s') return "string";
	if(t=='n') return "number";
	if(t=='p') return "pair";
	if(t=='a') return "array";
	return "unknown"; 
}

inline string error_string(const char *list_name,string lst,const char f,const char l)
{
	return string("Incorrect element in ")+list_name+" list: "+lst+"; "+type_to_name(f) + " : "+type_to_name(l) +" expected";
}


inline PairParameter *get_valid_pair( Parameter *p,const char *list_name,const char f,const char s)
{
	if(p->getType() != Parameter::PAIR)
	{
		throw new Exception(NULL,error_string(list_name,p->toString(),f,s).c_str());
	}

	PairParameter *pp = (PairParameter *)p;
	if(!check_type(pp->getFirstPtr(),f) || !check_type(pp->getSecondPtr(),s) )
	{
		throw new Exception(NULL,error_string(list_name,p->toString(),f,s).c_str());
	}

	return (PairParameter *)p;
}

template<typename T>
inline void get_value(Parameter *p,T *dat)
{
	if(p->getType() == Parameter::STRING)
		*((const char **)dat) = p->getStringPtr();
	if(p->getType() == Parameter::DOUBLE)
		*((Real *)dat) = p->getDouble();
}


template<typename FirstType,typename SecondType>
inline void get_pair_values(PairParameter *p,FirstType *f,SecondType *s)
{
	get_value(p->getFirstPtr(),f);
	get_value(p->getSecondPtr(),s);	
}

ParametersAdaptor1DRISM::ParametersAdaptor1DRISM(Parameters *parameters) 
: ParametersAdaptor(parameters)
{

m_densities = NULL;
m_distMatrix = NULL;
m_siteNames = NULL;
m_sigma = NULL;
m_epsilon = NULL;
m_charge = NULL;
m_nsites=0;
}

void ParametersAdaptor1DRISM::init()
{
fill_mol_dens_map();
read_sites();
m_sigma = read_site_data("sigma");
m_epsilon = read_site_data("epsilon");
m_charge = read_site_data("charge");
read_distances();
}

ParametersAdaptor1DRISM::~ParametersAdaptor1DRISM()
{


#define NDEL(x)  if(x) delete x; x=NULL;

NDEL(m_densities)
NULL_DELETE(m_distMatrix)

if(m_siteNames)
{	int i;
	for(i=0;i<m_nsites;i++)
		if(m_siteNames[i]) free((void *)m_siteNames[i]);
}
NDEL(m_siteNames)
NDEL(m_sigma)
NDEL(m_epsilon)
NDEL(m_charge)

#undef NDEL

}

void ParametersAdaptor1DRISM::fill_mol_dens_map()
{

vector<Parameter *> *mol_dens_list = this->getArrayParameter( "densities" );
vector<Parameter *>::iterator it;
for(it=mol_dens_list->begin(); it!=mol_dens_list->end(); it++)
{
	PairParameter *p = get_valid_pair(*it,"densities",'s','n');
	const char *molnam;
	Real dens;
	get_pair_values(p,&molnam,&dens);
	m_mol_dens_map[molnam] = dens;
} // for

}// fill_mol_dens_map

void ParametersAdaptor1DRISM::read_sites()
{

vector<Parameter *> *site_list = this->getArrayParameter("sites");

m_nsites = site_list->size();

m_densities = new Real[m_nsites];
m_siteNames = new const char*[m_nsites];

int i;
for(i=0;i<m_nsites;i++)
	m_siteNames[i] = NULL;

vector<Parameter *>::iterator it;
int site_id = 0;
for(it=site_list->begin(); it!=site_list->end(); it++, site_id ++ )
{
	bool mol_dens = true;
	const char *site, * mol;
	Real dens;
	PairParameter *p;

	try{ // format site : molecule
		p = get_valid_pair(*it,"sites",'s','s');

		get_pair_values(p,&site,&mol);
	
		map<string,Real>::iterator mit = m_mol_dens_map.find(mol);
 		if(mit == m_mol_dens_map.end())
		{
			string s = string("sites list: molecule ") + mol +" not found in densities";
			throw new Exception(NULL,s.c_str());
		}		

		dens = (*mit).second;

	} catch(Exception *e)	{
	try{  // format site : density
		mol_dens = false;

		p = get_valid_pair(*it,"sites",'s','n');
		get_pair_values(p,&site,&dens);

	} catch(Exception *e1) {

			string s(e->toString());
			s = s +  " OR " + e1->toString();
	
			throw new Exception(this,s.c_str());
	}}

	const char *site_copy = (const char *)strdup(site);
	m_siteNames[site_id] = site_copy;
	m_site_name_map[site_copy] = site_id;

	m_densities[site_id] = dens;
}//for it

}


Real *ParametersAdaptor1DRISM::read_site_data(const char *list_name)
{

vector<Parameter *> *l = this->getArrayParameter(list_name);
vector<Parameter *>::iterator it;


if(m_nsites != l->size())
{
	string err = string("Length of list ") + list_name + "does not match the number of sites!";
	throw new Exception(this,err.c_str());
}


Real *arr = new Real[m_nsites];
int *present = new int[m_nsites];

int i;
for(i=0;i<m_nsites;i++) present[i] = 0;

PairParameter *p;
const char *site;
Real val;
Integer site_id;
for(it = l->begin(); it!=l->end(); it++)
{
	p = get_valid_pair(*it,"sites",'s','n');
	get_pair_values(p,&site,&val);

	map<string,Integer>::iterator mit = m_site_name_map.find(site);
	if( mit == m_site_name_map.end())
	{
		string err = string("Invalid site name: ") + site + " in list:" + list_name;
		throw new Exception(this,err.c_str());	
	}

	site_id = (*mit).second;
	if(present[site_id])
	{
		string err = string("Duplicated site ") + site + " in list " + list_name;
		throw new Exception(this,err.c_str());
	}
	
	present[site_id] = 1;
	arr[site_id] = val;
}

delete present;
return arr;
}

void ParametersAdaptor1DRISM::read_distances()
{
m_distMatrix = new SimpleMatrix<Real>(m_nsites,m_nsites);

int i,j;

	
vector<Parameter *> *dlist = this->getArrayParameter("distances");
vector<Parameter *>::iterator it;

PairParameter *p;
const char *site1,*site2;
Real dist;
PairParameter *site_pair;

for(i=0;i<m_nsites;i++)
for(j=0;j<m_nsites;j++)
   m_distMatrix->setAt(i,j,0.0);

map<string,Integer>::iterator mit;
Integer site1_id,site2_id;
for(it = dlist->begin(); it!=dlist->end(); it++)
{
	p = get_valid_pair(*it,"distances",'p','n');

        std::cout<<p->toString()<<std::endl;

        site_pair = get_valid_pair(p->getFirstPtr(),"distances",'s','s');
        get_value(p->getSecondPtr(),&dist);

 	std::cout<<site_pair->toString()<<std::endl;

 	get_pair_values(site_pair,&site1,&site2);
	
	std::cout<<site1<<"--"<<site2<<endl;
	
	mit = m_site_name_map.find(site1);
	if( mit == m_site_name_map.end())
	{
		string err = string("Invalid site name: ") + site1 + " in list distances";
		throw new Exception(this,err.c_str());	
	}

	site1_id = (*mit).second;

	mit = m_site_name_map.find(site2);
	if( mit == m_site_name_map.end())
	{
		string err = string("Invalid site name: ") + site2 + " in list distances";
		throw new Exception(this,err.c_str());	
	}

	site2_id = (*mit).second;

	m_distMatrix->setAt(site1_id,site2_id,dist);
	m_distMatrix->setAt(site2_id,site1_id,dist);

}

}
