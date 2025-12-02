// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__Ne
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "./T6He2Event.h"
#include "./TNeAnalysis.h"
#include "./TNeDet16.h"
#include "./TNeEvent.h"
#include "./TNeMParms.h"
#include "./TNeProc.h"
#include "./TNeSel.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_T6He2Event(void *p = nullptr);
   static void *newArray_T6He2Event(Long_t size, void *p);
   static void delete_T6He2Event(void *p);
   static void deleteArray_T6He2Event(void *p);
   static void destruct_T6He2Event(void *p);
   static void streamer_T6He2Event(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::T6He2Event*)
   {
      ::T6He2Event *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::T6He2Event >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("T6He2Event", ::T6He2Event::Class_Version(), "T6He2Event.h", 12,
                  typeid(::T6He2Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::T6He2Event::Dictionary, isa_proxy, 16,
                  sizeof(::T6He2Event) );
      instance.SetNew(&new_T6He2Event);
      instance.SetNewArray(&newArray_T6He2Event);
      instance.SetDelete(&delete_T6He2Event);
      instance.SetDeleteArray(&deleteArray_T6He2Event);
      instance.SetDestructor(&destruct_T6He2Event);
      instance.SetStreamerFunc(&streamer_T6He2Event);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::T6He2Event*)
   {
      return GenerateInitInstanceLocal(static_cast<::T6He2Event*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::T6He2Event*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TNeAnalysis(void *p = nullptr);
   static void *newArray_TNeAnalysis(Long_t size, void *p);
   static void delete_TNeAnalysis(void *p);
   static void deleteArray_TNeAnalysis(void *p);
   static void destruct_TNeAnalysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TNeAnalysis*)
   {
      ::TNeAnalysis *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TNeAnalysis >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TNeAnalysis", ::TNeAnalysis::Class_Version(), "TNeAnalysis.h", 17,
                  typeid(::TNeAnalysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TNeAnalysis::Dictionary, isa_proxy, 4,
                  sizeof(::TNeAnalysis) );
      instance.SetNew(&new_TNeAnalysis);
      instance.SetNewArray(&newArray_TNeAnalysis);
      instance.SetDelete(&delete_TNeAnalysis);
      instance.SetDeleteArray(&deleteArray_TNeAnalysis);
      instance.SetDestructor(&destruct_TNeAnalysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TNeAnalysis*)
   {
      return GenerateInitInstanceLocal(static_cast<::TNeAnalysis*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TNeAnalysis*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TNeDet16(void *p = nullptr);
   static void *newArray_TNeDet16(Long_t size, void *p);
   static void delete_TNeDet16(void *p);
   static void deleteArray_TNeDet16(void *p);
   static void destruct_TNeDet16(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TNeDet16*)
   {
      ::TNeDet16 *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TNeDet16 >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TNeDet16", ::TNeDet16::Class_Version(), "TNeDet16.h", 11,
                  typeid(::TNeDet16), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TNeDet16::Dictionary, isa_proxy, 4,
                  sizeof(::TNeDet16) );
      instance.SetNew(&new_TNeDet16);
      instance.SetNewArray(&newArray_TNeDet16);
      instance.SetDelete(&delete_TNeDet16);
      instance.SetDeleteArray(&deleteArray_TNeDet16);
      instance.SetDestructor(&destruct_TNeDet16);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TNeDet16*)
   {
      return GenerateInitInstanceLocal(static_cast<::TNeDet16*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TNeDet16*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TNeEvent(void *p = nullptr);
   static void *newArray_TNeEvent(Long_t size, void *p);
   static void delete_TNeEvent(void *p);
   static void deleteArray_TNeEvent(void *p);
   static void destruct_TNeEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TNeEvent*)
   {
      ::TNeEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TNeEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TNeEvent", ::TNeEvent::Class_Version(), "TNeEvent.h", 12,
                  typeid(::TNeEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TNeEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TNeEvent) );
      instance.SetNew(&new_TNeEvent);
      instance.SetNewArray(&newArray_TNeEvent);
      instance.SetDelete(&delete_TNeEvent);
      instance.SetDeleteArray(&deleteArray_TNeEvent);
      instance.SetDestructor(&destruct_TNeEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TNeEvent*)
   {
      return GenerateInitInstanceLocal(static_cast<::TNeEvent*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TNeEvent*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TNeMParms(void *p = nullptr);
   static void *newArray_TNeMParms(Long_t size, void *p);
   static void delete_TNeMParms(void *p);
   static void deleteArray_TNeMParms(void *p);
   static void destruct_TNeMParms(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TNeMParms*)
   {
      ::TNeMParms *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TNeMParms >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TNeMParms", ::TNeMParms::Class_Version(), "TNeMParms.h", 11,
                  typeid(::TNeMParms), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TNeMParms::Dictionary, isa_proxy, 4,
                  sizeof(::TNeMParms) );
      instance.SetNew(&new_TNeMParms);
      instance.SetNewArray(&newArray_TNeMParms);
      instance.SetDelete(&delete_TNeMParms);
      instance.SetDeleteArray(&deleteArray_TNeMParms);
      instance.SetDestructor(&destruct_TNeMParms);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TNeMParms*)
   {
      return GenerateInitInstanceLocal(static_cast<::TNeMParms*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TNeMParms*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TNeProc(void *p = nullptr);
   static void *newArray_TNeProc(Long_t size, void *p);
   static void delete_TNeProc(void *p);
   static void deleteArray_TNeProc(void *p);
   static void destruct_TNeProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TNeProc*)
   {
      ::TNeProc *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TNeProc >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TNeProc", ::TNeProc::Class_Version(), "TNeProc.h", 16,
                  typeid(::TNeProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TNeProc::Dictionary, isa_proxy, 4,
                  sizeof(::TNeProc) );
      instance.SetNew(&new_TNeProc);
      instance.SetNewArray(&newArray_TNeProc);
      instance.SetDelete(&delete_TNeProc);
      instance.SetDeleteArray(&deleteArray_TNeProc);
      instance.SetDestructor(&destruct_TNeProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TNeProc*)
   {
      return GenerateInitInstanceLocal(static_cast<::TNeProc*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TNeProc*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TNeSel(void *p = nullptr);
   static void *newArray_TNeSel(Long_t size, void *p);
   static void delete_TNeSel(void *p);
   static void deleteArray_TNeSel(void *p);
   static void destruct_TNeSel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TNeSel*)
   {
      ::TNeSel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TNeSel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TNeSel", ::TNeSel::Class_Version(), "TNeSel.h", 11,
                  typeid(::TNeSel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TNeSel::Dictionary, isa_proxy, 4,
                  sizeof(::TNeSel) );
      instance.SetNew(&new_TNeSel);
      instance.SetNewArray(&newArray_TNeSel);
      instance.SetDelete(&delete_TNeSel);
      instance.SetDeleteArray(&deleteArray_TNeSel);
      instance.SetDestructor(&destruct_TNeSel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TNeSel*)
   {
      return GenerateInitInstanceLocal(static_cast<::TNeSel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TNeSel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr T6He2Event::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *T6He2Event::Class_Name()
{
   return "T6He2Event";
}

//______________________________________________________________________________
const char *T6He2Event::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::T6He2Event*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int T6He2Event::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::T6He2Event*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *T6He2Event::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::T6He2Event*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *T6He2Event::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::T6He2Event*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TNeAnalysis::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeAnalysis::Class_Name()
{
   return "TNeAnalysis";
}

//______________________________________________________________________________
const char *TNeAnalysis::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeAnalysis*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TNeAnalysis::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeAnalysis*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeAnalysis::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeAnalysis*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeAnalysis::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeAnalysis*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TNeDet16::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeDet16::Class_Name()
{
   return "TNeDet16";
}

//______________________________________________________________________________
const char *TNeDet16::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeDet16*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TNeDet16::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeDet16*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeDet16::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeDet16*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeDet16::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeDet16*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TNeEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeEvent::Class_Name()
{
   return "TNeEvent";
}

//______________________________________________________________________________
const char *TNeEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TNeEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TNeMParms::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeMParms::Class_Name()
{
   return "TNeMParms";
}

//______________________________________________________________________________
const char *TNeMParms::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeMParms*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TNeMParms::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeMParms*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeMParms::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeMParms*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeMParms::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeMParms*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TNeProc::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeProc::Class_Name()
{
   return "TNeProc";
}

//______________________________________________________________________________
const char *TNeProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeProc*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TNeProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeProc*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeProc*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeProc*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TNeSel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeSel::Class_Name()
{
   return "TNeSel";
}

//______________________________________________________________________________
const char *TNeSel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeSel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TNeSel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNeSel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeSel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeSel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeSel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNeSel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void T6He2Event::Streamer(TBuffer &R__b)
{
   // Stream an object of class T6He2Event.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGo4EventElement::Streamer(R__b);
      R__b >> beam_beta;
      R__b >> beam_gamma;
      R__b.CheckByteCount(R__s, R__c, T6He2Event::IsA());
   } else {
      R__c = R__b.WriteVersion(T6He2Event::IsA(), kTRUE);
      TGo4EventElement::Streamer(R__b);
      R__b << beam_beta;
      R__b << beam_gamma;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_T6He2Event(void *p) {
      return  p ? new(p) ::T6He2Event : new ::T6He2Event;
   }
   static void *newArray_T6He2Event(Long_t nElements, void *p) {
      return p ? new(p) ::T6He2Event[nElements] : new ::T6He2Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_T6He2Event(void *p) {
      delete (static_cast<::T6He2Event*>(p));
   }
   static void deleteArray_T6He2Event(void *p) {
      delete [] (static_cast<::T6He2Event*>(p));
   }
   static void destruct_T6He2Event(void *p) {
      typedef ::T6He2Event current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_T6He2Event(TBuffer &buf, void *obj) {
      ((::T6He2Event*)obj)->::T6He2Event::Streamer(buf);
   }
} // end of namespace ROOT for class ::T6He2Event

//______________________________________________________________________________
void TNeAnalysis::Streamer(TBuffer &R__b)
{
   // Stream an object of class TNeAnalysis.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TNeAnalysis::Class(),this);
   } else {
      R__b.WriteClassBuffer(TNeAnalysis::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TNeAnalysis(void *p) {
      return  p ? new(p) ::TNeAnalysis : new ::TNeAnalysis;
   }
   static void *newArray_TNeAnalysis(Long_t nElements, void *p) {
      return p ? new(p) ::TNeAnalysis[nElements] : new ::TNeAnalysis[nElements];
   }
   // Wrapper around operator delete
   static void delete_TNeAnalysis(void *p) {
      delete (static_cast<::TNeAnalysis*>(p));
   }
   static void deleteArray_TNeAnalysis(void *p) {
      delete [] (static_cast<::TNeAnalysis*>(p));
   }
   static void destruct_TNeAnalysis(void *p) {
      typedef ::TNeAnalysis current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TNeAnalysis

//______________________________________________________________________________
void TNeDet16::Streamer(TBuffer &R__b)
{
   // Stream an object of class TNeDet16.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TNeDet16::Class(),this);
   } else {
      R__b.WriteClassBuffer(TNeDet16::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TNeDet16(void *p) {
      return  p ? new(p) ::TNeDet16 : new ::TNeDet16;
   }
   static void *newArray_TNeDet16(Long_t nElements, void *p) {
      return p ? new(p) ::TNeDet16[nElements] : new ::TNeDet16[nElements];
   }
   // Wrapper around operator delete
   static void delete_TNeDet16(void *p) {
      delete (static_cast<::TNeDet16*>(p));
   }
   static void deleteArray_TNeDet16(void *p) {
      delete [] (static_cast<::TNeDet16*>(p));
   }
   static void destruct_TNeDet16(void *p) {
      typedef ::TNeDet16 current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TNeDet16

//______________________________________________________________________________
void TNeEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TNeEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TNeEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TNeEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TNeEvent(void *p) {
      return  p ? new(p) ::TNeEvent : new ::TNeEvent;
   }
   static void *newArray_TNeEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TNeEvent[nElements] : new ::TNeEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TNeEvent(void *p) {
      delete (static_cast<::TNeEvent*>(p));
   }
   static void deleteArray_TNeEvent(void *p) {
      delete [] (static_cast<::TNeEvent*>(p));
   }
   static void destruct_TNeEvent(void *p) {
      typedef ::TNeEvent current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TNeEvent

//______________________________________________________________________________
void TNeMParms::Streamer(TBuffer &R__b)
{
   // Stream an object of class TNeMParms.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TNeMParms::Class(),this);
   } else {
      R__b.WriteClassBuffer(TNeMParms::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TNeMParms(void *p) {
      return  p ? new(p) ::TNeMParms : new ::TNeMParms;
   }
   static void *newArray_TNeMParms(Long_t nElements, void *p) {
      return p ? new(p) ::TNeMParms[nElements] : new ::TNeMParms[nElements];
   }
   // Wrapper around operator delete
   static void delete_TNeMParms(void *p) {
      delete (static_cast<::TNeMParms*>(p));
   }
   static void deleteArray_TNeMParms(void *p) {
      delete [] (static_cast<::TNeMParms*>(p));
   }
   static void destruct_TNeMParms(void *p) {
      typedef ::TNeMParms current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TNeMParms

//______________________________________________________________________________
void TNeProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class TNeProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TNeProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(TNeProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TNeProc(void *p) {
      return  p ? new(p) ::TNeProc : new ::TNeProc;
   }
   static void *newArray_TNeProc(Long_t nElements, void *p) {
      return p ? new(p) ::TNeProc[nElements] : new ::TNeProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_TNeProc(void *p) {
      delete (static_cast<::TNeProc*>(p));
   }
   static void deleteArray_TNeProc(void *p) {
      delete [] (static_cast<::TNeProc*>(p));
   }
   static void destruct_TNeProc(void *p) {
      typedef ::TNeProc current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TNeProc

//______________________________________________________________________________
void TNeSel::Streamer(TBuffer &R__b)
{
   // Stream an object of class TNeSel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TNeSel::Class(),this);
   } else {
      R__b.WriteClassBuffer(TNeSel::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TNeSel(void *p) {
      return  p ? new(p) ::TNeSel : new ::TNeSel;
   }
   static void *newArray_TNeSel(Long_t nElements, void *p) {
      return p ? new(p) ::TNeSel[nElements] : new ::TNeSel[nElements];
   }
   // Wrapper around operator delete
   static void delete_TNeSel(void *p) {
      delete (static_cast<::TNeSel*>(p));
   }
   static void deleteArray_TNeSel(void *p) {
      delete [] (static_cast<::TNeSel*>(p));
   }
   static void destruct_TNeSel(void *p) {
      typedef ::TNeSel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TNeSel

namespace ROOT {
   // Registration Schema evolution read functions
   int RecordReadRules_libGo4UserAnalysis() {
      return 0;
   }
   static int _R__UNIQUE_DICT_(ReadRules_libGo4UserAnalysis) = RecordReadRules_libGo4UserAnalysis();R__UseDummy(_R__UNIQUE_DICT_(ReadRules_libGo4UserAnalysis));
} // namespace ROOT
namespace {
  void TriggerDictionaryInitialization_libGo4UserAnalysis_Impl() {
    static const char* headers[] = {
"./T6He2Event.h",
"./TNeAnalysis.h",
"./TNeDet16.h",
"./TNeEvent.h",
"./TNeMParms.h",
"./TNeProc.h",
"./TNeSel.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/long/go4/go4-6.4.0/include",
"/home/long/go4/go4-6.4.0",
"/home/long/root/root-source/pre-compiled/root/include/",
"/home/long/go4/go4_examples/25e10/go4/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libGo4UserAnalysis dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$./T6He2Event.h")))  T6He2Event;
class __attribute__((annotate("$clingAutoload$./TNeAnalysis.h")))  TNeAnalysis;
class __attribute__((annotate("$clingAutoload$./TNeDet16.h")))  TNeDet16;
class __attribute__((annotate("$clingAutoload$./TNeEvent.h")))  TNeEvent;
class __attribute__((annotate("$clingAutoload$./TNeMParms.h")))  TNeMParms;
class __attribute__((annotate("$clingAutoload$./TNeProc.h")))  TNeProc;
class __attribute__((annotate("$clingAutoload$./TNeSel.h")))  TNeSel;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libGo4UserAnalysis dictionary payload"

#ifndef Linux
  #define Linux 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "./T6He2Event.h"
#include "./TNeAnalysis.h"
#include "./TNeDet16.h"
#include "./TNeEvent.h"
#include "./TNeMParms.h"
#include "./TNeProc.h"
#include "./TNeSel.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"T6He2Event", payloadCode, "@",
"TNeAnalysis", payloadCode, "@",
"TNeDet16", payloadCode, "@",
"TNeEvent", payloadCode, "@",
"TNeMParms", payloadCode, "@",
"TNeProc", payloadCode, "@",
"TNeSel", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libGo4UserAnalysis",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libGo4UserAnalysis_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libGo4UserAnalysis_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libGo4UserAnalysis() {
  TriggerDictionaryInitialization_libGo4UserAnalysis_Impl();
}
