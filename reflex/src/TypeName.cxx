// @(#)root/reflex:$Id: TypeName.cxx,v 1.11 2006/07/04 15:02:55 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2006, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef REFLEX_BUILD
#define REFLEX_BUILD
#endif

#include "Reflex/TypeName.h"

#include "Reflex/Type.h"
#include "Reflex/Member.h"

#include "stl_hash.h"
#include <vector>


//-------------------------------------------------------------------------------
typedef __gnu_cxx::hash_map<const char *, ROOT::Reflex::TypeName * > Name2Type_t;
typedef __gnu_cxx::hash_map<const char *, ROOT::Reflex::TypeName * > TypeId2Type_t;
typedef std::vector< ROOT::Reflex::Type > TypeVec_t;


//-------------------------------------------------------------------------------
static Name2Type_t & sTypes() {
//-------------------------------------------------------------------------------
// Static wrapper for type map.
   static Name2Type_t m;
   return m;
}


//-------------------------------------------------------------------------------
static TypeId2Type_t & sTypeInfos() {
//-------------------------------------------------------------------------------
// Static wrapper for type map (type_infos).
   static TypeId2Type_t m;
   return m;
}


//-------------------------------------------------------------------------------
static TypeVec_t & sTypeVec() {
//-------------------------------------------------------------------------------
// Static wrapper for type vector.
   static TypeVec_t m;
   return m;
}


//-------------------------------------------------------------------------------
ROOT::Reflex::TypeName::TypeName( const char * nam,
                                  TypeBase * typeBas,
                                  const std::type_info * ti )
   : fName( nam ),
     fTypeBase( typeBas ) {
//-------------------------------------------------------------------------------
// Construct a type name.
   sTypes() [ fName.c_str() ] = this;
   sTypeVec().push_back(Type(this));
   if ( ti ) sTypeInfos() [ ti->name() ] = this;
}


//-------------------------------------------------------------------------------
ROOT::Reflex::TypeName::~TypeName() {
//-------------------------------------------------------------------------------
// Destructor.
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::TypeName::SetTypeId( const std::type_info & ti ) const {
//-------------------------------------------------------------------------------
// Add a type_info to the map.
   sTypeInfos() [ ti.name() ] = const_cast<TypeName*>(this);
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type
ROOT::Reflex::TypeName::ByName( const std::string & key ) {
//-------------------------------------------------------------------------------
// Lookup a type by name.
   size_t pos =  key.substr(0,2) == "::" ?  2 : 0;
   Name2Type_t::iterator it = sTypes().find(key.substr(pos).c_str());
   if( it != sTypes().end() ) return Type( it->second );
   else                       return Type();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type
ROOT::Reflex::TypeName::ByTypeInfo( const std::type_info & ti ) {
//-------------------------------------------------------------------------------
// Lookup a type by type_info.
   TypeId2Type_t::iterator it = sTypeInfos().find(ti.name());
   if( it != sTypeInfos().end() ) return Type( it->second );
   else                           return Type();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::TypeName::ThisType() const {
//-------------------------------------------------------------------------------
// Return Type of this TypeName.
   return Type( this );
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::TypeName::TypeAt( size_t nth ) {
//-------------------------------------------------------------------------------
// Return nth type in Reflex.
   if ( nth < sTypeVec().size()) return sTypeVec()[nth];
   return Type();
}


//-------------------------------------------------------------------------------
size_t ROOT::Reflex::TypeName::TypeSize() {
//-------------------------------------------------------------------------------
// Return number of types in Reflex.
   return sTypeVec().size();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type_Iterator ROOT::Reflex::TypeName::Type_Begin() {
//-------------------------------------------------------------------------------
// Return begin iterator of the type container.
   return sTypeVec().begin();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type_Iterator ROOT::Reflex::TypeName::Type_End() {
//-------------------------------------------------------------------------------
// Return end iterator of the type container.
   return sTypeVec().end();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::TypeName::Type_RBegin() {
//-------------------------------------------------------------------------------
// Return rbegin iterator of the type container.
   return sTypeVec().rbegin();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::TypeName::Type_REnd() {
//-------------------------------------------------------------------------------
// Return rend iterator of the type container.
   return sTypeVec().rend();
}


