// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME modulesdIFemtoDstFormatdIDictionaryFemtoDst

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
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

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "FemtoBTofPidTraits.h"
#include "FemtoEvent.h"
#include "FemtoMcTrack.h"
#include "FemtoMcVertex.h"
#include "FemtoMtdPidTraits.h"
#include "FemtoTrack.h"
#include "FemtoTrackHelix.h"
#include "FemtoDstBranch.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_FemtoDstBranch(void *p);
   static void deleteArray_FemtoDstBranch(void *p);
   static void destruct_FemtoDstBranch(void *p);
   static void streamer_FemtoDstBranch(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FemtoDstBranch*)
   {
      ::FemtoDstBranch *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FemtoDstBranch >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FemtoDstBranch", ::FemtoDstBranch::Class_Version(), "FemtoDstBranch.h", 6,
                  typeid(::FemtoDstBranch), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FemtoDstBranch::Dictionary, isa_proxy, 16,
                  sizeof(::FemtoDstBranch) );
      instance.SetDelete(&delete_FemtoDstBranch);
      instance.SetDeleteArray(&deleteArray_FemtoDstBranch);
      instance.SetDestructor(&destruct_FemtoDstBranch);
      instance.SetStreamerFunc(&streamer_FemtoDstBranch);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FemtoDstBranch*)
   {
      return GenerateInitInstanceLocal((::FemtoDstBranch*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FemtoDstBranch*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FemtoBTofPidTraits(void *p = 0);
   static void *newArray_FemtoBTofPidTraits(Long_t size, void *p);
   static void delete_FemtoBTofPidTraits(void *p);
   static void deleteArray_FemtoBTofPidTraits(void *p);
   static void destruct_FemtoBTofPidTraits(void *p);
   static void streamer_FemtoBTofPidTraits(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FemtoBTofPidTraits*)
   {
      ::FemtoBTofPidTraits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FemtoBTofPidTraits >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FemtoBTofPidTraits", ::FemtoBTofPidTraits::Class_Version(), "FemtoBTofPidTraits.h", 7,
                  typeid(::FemtoBTofPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FemtoBTofPidTraits::Dictionary, isa_proxy, 16,
                  sizeof(::FemtoBTofPidTraits) );
      instance.SetNew(&new_FemtoBTofPidTraits);
      instance.SetNewArray(&newArray_FemtoBTofPidTraits);
      instance.SetDelete(&delete_FemtoBTofPidTraits);
      instance.SetDeleteArray(&deleteArray_FemtoBTofPidTraits);
      instance.SetDestructor(&destruct_FemtoBTofPidTraits);
      instance.SetStreamerFunc(&streamer_FemtoBTofPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FemtoBTofPidTraits*)
   {
      return GenerateInitInstanceLocal((::FemtoBTofPidTraits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FemtoBTofPidTraits*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FemtoEvent(void *p = 0);
   static void *newArray_FemtoEvent(Long_t size, void *p);
   static void delete_FemtoEvent(void *p);
   static void deleteArray_FemtoEvent(void *p);
   static void destruct_FemtoEvent(void *p);
   static void streamer_FemtoEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FemtoEvent*)
   {
      ::FemtoEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FemtoEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FemtoEvent", ::FemtoEvent::Class_Version(), "FemtoEvent.h", 6,
                  typeid(::FemtoEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FemtoEvent::Dictionary, isa_proxy, 16,
                  sizeof(::FemtoEvent) );
      instance.SetNew(&new_FemtoEvent);
      instance.SetNewArray(&newArray_FemtoEvent);
      instance.SetDelete(&delete_FemtoEvent);
      instance.SetDeleteArray(&deleteArray_FemtoEvent);
      instance.SetDestructor(&destruct_FemtoEvent);
      instance.SetStreamerFunc(&streamer_FemtoEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FemtoEvent*)
   {
      return GenerateInitInstanceLocal((::FemtoEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FemtoEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FemtoMcTrack(void *p = 0);
   static void *newArray_FemtoMcTrack(Long_t size, void *p);
   static void delete_FemtoMcTrack(void *p);
   static void deleteArray_FemtoMcTrack(void *p);
   static void destruct_FemtoMcTrack(void *p);
   static void streamer_FemtoMcTrack(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FemtoMcTrack*)
   {
      ::FemtoMcTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FemtoMcTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FemtoMcTrack", ::FemtoMcTrack::Class_Version(), "FemtoMcTrack.h", 11,
                  typeid(::FemtoMcTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FemtoMcTrack::Dictionary, isa_proxy, 16,
                  sizeof(::FemtoMcTrack) );
      instance.SetNew(&new_FemtoMcTrack);
      instance.SetNewArray(&newArray_FemtoMcTrack);
      instance.SetDelete(&delete_FemtoMcTrack);
      instance.SetDeleteArray(&deleteArray_FemtoMcTrack);
      instance.SetDestructor(&destruct_FemtoMcTrack);
      instance.SetStreamerFunc(&streamer_FemtoMcTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FemtoMcTrack*)
   {
      return GenerateInitInstanceLocal((::FemtoMcTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FemtoMcTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FemtoMcVertex(void *p = 0);
   static void *newArray_FemtoMcVertex(Long_t size, void *p);
   static void delete_FemtoMcVertex(void *p);
   static void deleteArray_FemtoMcVertex(void *p);
   static void destruct_FemtoMcVertex(void *p);
   static void streamer_FemtoMcVertex(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FemtoMcVertex*)
   {
      ::FemtoMcVertex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FemtoMcVertex >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FemtoMcVertex", ::FemtoMcVertex::Class_Version(), "FemtoMcVertex.h", 16,
                  typeid(::FemtoMcVertex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FemtoMcVertex::Dictionary, isa_proxy, 16,
                  sizeof(::FemtoMcVertex) );
      instance.SetNew(&new_FemtoMcVertex);
      instance.SetNewArray(&newArray_FemtoMcVertex);
      instance.SetDelete(&delete_FemtoMcVertex);
      instance.SetDeleteArray(&deleteArray_FemtoMcVertex);
      instance.SetDestructor(&destruct_FemtoMcVertex);
      instance.SetStreamerFunc(&streamer_FemtoMcVertex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FemtoMcVertex*)
   {
      return GenerateInitInstanceLocal((::FemtoMcVertex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FemtoMcVertex*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FemtoMtdPidTraits(void *p = 0);
   static void *newArray_FemtoMtdPidTraits(Long_t size, void *p);
   static void delete_FemtoMtdPidTraits(void *p);
   static void deleteArray_FemtoMtdPidTraits(void *p);
   static void destruct_FemtoMtdPidTraits(void *p);
   static void streamer_FemtoMtdPidTraits(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FemtoMtdPidTraits*)
   {
      ::FemtoMtdPidTraits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FemtoMtdPidTraits >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FemtoMtdPidTraits", ::FemtoMtdPidTraits::Class_Version(), "FemtoMtdPidTraits.h", 7,
                  typeid(::FemtoMtdPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FemtoMtdPidTraits::Dictionary, isa_proxy, 16,
                  sizeof(::FemtoMtdPidTraits) );
      instance.SetNew(&new_FemtoMtdPidTraits);
      instance.SetNewArray(&newArray_FemtoMtdPidTraits);
      instance.SetDelete(&delete_FemtoMtdPidTraits);
      instance.SetDeleteArray(&deleteArray_FemtoMtdPidTraits);
      instance.SetDestructor(&destruct_FemtoMtdPidTraits);
      instance.SetStreamerFunc(&streamer_FemtoMtdPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FemtoMtdPidTraits*)
   {
      return GenerateInitInstanceLocal((::FemtoMtdPidTraits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FemtoMtdPidTraits*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FemtoTrack(void *p = 0);
   static void *newArray_FemtoTrack(Long_t size, void *p);
   static void delete_FemtoTrack(void *p);
   static void deleteArray_FemtoTrack(void *p);
   static void destruct_FemtoTrack(void *p);
   static void streamer_FemtoTrack(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FemtoTrack*)
   {
      ::FemtoTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FemtoTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FemtoTrack", ::FemtoTrack::Class_Version(), "FemtoTrack.h", 10,
                  typeid(::FemtoTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FemtoTrack::Dictionary, isa_proxy, 16,
                  sizeof(::FemtoTrack) );
      instance.SetNew(&new_FemtoTrack);
      instance.SetNewArray(&newArray_FemtoTrack);
      instance.SetDelete(&delete_FemtoTrack);
      instance.SetDeleteArray(&deleteArray_FemtoTrack);
      instance.SetDestructor(&destruct_FemtoTrack);
      instance.SetStreamerFunc(&streamer_FemtoTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FemtoTrack*)
   {
      return GenerateInitInstanceLocal((::FemtoTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FemtoTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FemtoTrackHelix(void *p = 0);
   static void *newArray_FemtoTrackHelix(Long_t size, void *p);
   static void delete_FemtoTrackHelix(void *p);
   static void deleteArray_FemtoTrackHelix(void *p);
   static void destruct_FemtoTrackHelix(void *p);
   static void streamer_FemtoTrackHelix(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FemtoTrackHelix*)
   {
      ::FemtoTrackHelix *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FemtoTrackHelix >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FemtoTrackHelix", ::FemtoTrackHelix::Class_Version(), "FemtoTrackHelix.h", 7,
                  typeid(::FemtoTrackHelix), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FemtoTrackHelix::Dictionary, isa_proxy, 16,
                  sizeof(::FemtoTrackHelix) );
      instance.SetNew(&new_FemtoTrackHelix);
      instance.SetNewArray(&newArray_FemtoTrackHelix);
      instance.SetDelete(&delete_FemtoTrackHelix);
      instance.SetDeleteArray(&deleteArray_FemtoTrackHelix);
      instance.SetDestructor(&destruct_FemtoTrackHelix);
      instance.SetStreamerFunc(&streamer_FemtoTrackHelix);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FemtoTrackHelix*)
   {
      return GenerateInitInstanceLocal((::FemtoTrackHelix*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FemtoTrackHelix*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FemtoDstBranch::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FemtoDstBranch::Class_Name()
{
   return "FemtoDstBranch";
}

//______________________________________________________________________________
const char *FemtoDstBranch::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoDstBranch*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FemtoDstBranch::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoDstBranch*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FemtoDstBranch::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoDstBranch*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FemtoDstBranch::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoDstBranch*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FemtoBTofPidTraits::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FemtoBTofPidTraits::Class_Name()
{
   return "FemtoBTofPidTraits";
}

//______________________________________________________________________________
const char *FemtoBTofPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoBTofPidTraits*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FemtoBTofPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoBTofPidTraits*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FemtoBTofPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoBTofPidTraits*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FemtoBTofPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoBTofPidTraits*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FemtoEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FemtoEvent::Class_Name()
{
   return "FemtoEvent";
}

//______________________________________________________________________________
const char *FemtoEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FemtoEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FemtoEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FemtoEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FemtoMcTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FemtoMcTrack::Class_Name()
{
   return "FemtoMcTrack";
}

//______________________________________________________________________________
const char *FemtoMcTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoMcTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FemtoMcTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoMcTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FemtoMcTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoMcTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FemtoMcTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoMcTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FemtoMcVertex::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FemtoMcVertex::Class_Name()
{
   return "FemtoMcVertex";
}

//______________________________________________________________________________
const char *FemtoMcVertex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoMcVertex*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FemtoMcVertex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoMcVertex*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FemtoMcVertex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoMcVertex*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FemtoMcVertex::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoMcVertex*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FemtoMtdPidTraits::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FemtoMtdPidTraits::Class_Name()
{
   return "FemtoMtdPidTraits";
}

//______________________________________________________________________________
const char *FemtoMtdPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoMtdPidTraits*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FemtoMtdPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoMtdPidTraits*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FemtoMtdPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoMtdPidTraits*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FemtoMtdPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoMtdPidTraits*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FemtoTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FemtoTrack::Class_Name()
{
   return "FemtoTrack";
}

//______________________________________________________________________________
const char *FemtoTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FemtoTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FemtoTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FemtoTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FemtoTrackHelix::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FemtoTrackHelix::Class_Name()
{
   return "FemtoTrackHelix";
}

//______________________________________________________________________________
const char *FemtoTrackHelix::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoTrackHelix*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FemtoTrackHelix::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FemtoTrackHelix*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FemtoTrackHelix::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoTrackHelix*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FemtoTrackHelix::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FemtoTrackHelix*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FemtoDstBranch::Streamer(TBuffer &R__b)
{
   // Stream an object of class FemtoDstBranch.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, FemtoDstBranch::IsA());
   } else {
      R__c = R__b.WriteVersion(FemtoDstBranch::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FemtoDstBranch(void *p) {
      delete ((::FemtoDstBranch*)p);
   }
   static void deleteArray_FemtoDstBranch(void *p) {
      delete [] ((::FemtoDstBranch*)p);
   }
   static void destruct_FemtoDstBranch(void *p) {
      typedef ::FemtoDstBranch current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FemtoDstBranch(TBuffer &buf, void *obj) {
      ((::FemtoDstBranch*)obj)->::FemtoDstBranch::Streamer(buf);
   }
} // end of namespace ROOT for class ::FemtoDstBranch

//______________________________________________________________________________
void FemtoBTofPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class FemtoBTofPidTraits.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FemtoDstBranch::Streamer(R__b);
      R__b >> mBTofBeta;
      R__b >> mBTofYLocal;
      R__b >> mBTofZLocal;
      R__b >> mBTofMatchFlag;
      R__b >> mIdTruth;
      R__b.CheckByteCount(R__s, R__c, FemtoBTofPidTraits::IsA());
   } else {
      R__c = R__b.WriteVersion(FemtoBTofPidTraits::IsA(), kTRUE);
      FemtoDstBranch::Streamer(R__b);
      R__b << mBTofBeta;
      R__b << mBTofYLocal;
      R__b << mBTofZLocal;
      R__b << mBTofMatchFlag;
      R__b << mIdTruth;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FemtoBTofPidTraits(void *p) {
      return  p ? new(p) ::FemtoBTofPidTraits : new ::FemtoBTofPidTraits;
   }
   static void *newArray_FemtoBTofPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::FemtoBTofPidTraits[nElements] : new ::FemtoBTofPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_FemtoBTofPidTraits(void *p) {
      delete ((::FemtoBTofPidTraits*)p);
   }
   static void deleteArray_FemtoBTofPidTraits(void *p) {
      delete [] ((::FemtoBTofPidTraits*)p);
   }
   static void destruct_FemtoBTofPidTraits(void *p) {
      typedef ::FemtoBTofPidTraits current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FemtoBTofPidTraits(TBuffer &buf, void *obj) {
      ((::FemtoBTofPidTraits*)obj)->::FemtoBTofPidTraits::Streamer(buf);
   }
} // end of namespace ROOT for class ::FemtoBTofPidTraits

//______________________________________________________________________________
void FemtoEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class FemtoEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FemtoDstBranch::Streamer(R__b);
      R__b >> mPrimaryVertex_mX1;
      R__b >> mPrimaryVertex_mX2;
      R__b >> mPrimaryVertex_mX3;
      R__b >> mWeight;
      R__b >> mRunId;
      R__b >> mEventId;
      R__b >> mTriggerWord;
      R__b >> mTriggerWordMtd;
      R__b >> mGRefMult;
      R__b >> mPsi2;
      R__b >> mBin16;
      R__b >> mRunIndex;
      R__b.CheckByteCount(R__s, R__c, FemtoEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(FemtoEvent::IsA(), kTRUE);
      FemtoDstBranch::Streamer(R__b);
      R__b << mPrimaryVertex_mX1;
      R__b << mPrimaryVertex_mX2;
      R__b << mPrimaryVertex_mX3;
      R__b << mWeight;
      R__b << mRunId;
      R__b << mEventId;
      R__b << mTriggerWord;
      R__b << mTriggerWordMtd;
      R__b << mGRefMult;
      R__b << mPsi2;
      R__b << mBin16;
      R__b << mRunIndex;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FemtoEvent(void *p) {
      return  p ? new(p) ::FemtoEvent : new ::FemtoEvent;
   }
   static void *newArray_FemtoEvent(Long_t nElements, void *p) {
      return p ? new(p) ::FemtoEvent[nElements] : new ::FemtoEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_FemtoEvent(void *p) {
      delete ((::FemtoEvent*)p);
   }
   static void deleteArray_FemtoEvent(void *p) {
      delete [] ((::FemtoEvent*)p);
   }
   static void destruct_FemtoEvent(void *p) {
      typedef ::FemtoEvent current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FemtoEvent(TBuffer &buf, void *obj) {
      ((::FemtoEvent*)obj)->::FemtoEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::FemtoEvent

//______________________________________________________________________________
void FemtoMcTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class FemtoMcTrack.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FemtoDstBranch::Streamer(R__b);
      R__b >> mPt;
      R__b >> mEta;
      R__b >> mPhi;
      R__b >> mId;
      R__b >> mGeantPID;
      R__b >> mCharge;
      R__b >> mEnergy;
      R__b >> mNHits;
      R__b >> mParentIndex;
      R__b >> mAssociatedIndex;
      R__b >> mStartVertexIndex;
      R__b >> mStopVertexIndex;
      R__b.CheckByteCount(R__s, R__c, FemtoMcTrack::IsA());
   } else {
      R__c = R__b.WriteVersion(FemtoMcTrack::IsA(), kTRUE);
      FemtoDstBranch::Streamer(R__b);
      R__b << mPt;
      R__b << mEta;
      R__b << mPhi;
      R__b << mId;
      R__b << mGeantPID;
      R__b << mCharge;
      R__b << mEnergy;
      R__b << mNHits;
      R__b << mParentIndex;
      R__b << mAssociatedIndex;
      R__b << mStartVertexIndex;
      R__b << mStopVertexIndex;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FemtoMcTrack(void *p) {
      return  p ? new(p) ::FemtoMcTrack : new ::FemtoMcTrack;
   }
   static void *newArray_FemtoMcTrack(Long_t nElements, void *p) {
      return p ? new(p) ::FemtoMcTrack[nElements] : new ::FemtoMcTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_FemtoMcTrack(void *p) {
      delete ((::FemtoMcTrack*)p);
   }
   static void deleteArray_FemtoMcTrack(void *p) {
      delete [] ((::FemtoMcTrack*)p);
   }
   static void destruct_FemtoMcTrack(void *p) {
      typedef ::FemtoMcTrack current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FemtoMcTrack(TBuffer &buf, void *obj) {
      ((::FemtoMcTrack*)obj)->::FemtoMcTrack::Streamer(buf);
   }
} // end of namespace ROOT for class ::FemtoMcTrack

//______________________________________________________________________________
void FemtoMcVertex::Streamer(TBuffer &R__b)
{
   // Stream an object of class FemtoMcVertex.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FemtoDstBranch::Streamer(R__b);
      R__b >> mId;
      R__b >> mX;
      R__b >> mY;
      R__b >> mZ;
      R__b >> mParentIndex;
      R__b >> mGeantProcess;
      R__b.CheckByteCount(R__s, R__c, FemtoMcVertex::IsA());
   } else {
      R__c = R__b.WriteVersion(FemtoMcVertex::IsA(), kTRUE);
      FemtoDstBranch::Streamer(R__b);
      R__b << mId;
      R__b << mX;
      R__b << mY;
      R__b << mZ;
      R__b << mParentIndex;
      R__b << mGeantProcess;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FemtoMcVertex(void *p) {
      return  p ? new(p) ::FemtoMcVertex : new ::FemtoMcVertex;
   }
   static void *newArray_FemtoMcVertex(Long_t nElements, void *p) {
      return p ? new(p) ::FemtoMcVertex[nElements] : new ::FemtoMcVertex[nElements];
   }
   // Wrapper around operator delete
   static void delete_FemtoMcVertex(void *p) {
      delete ((::FemtoMcVertex*)p);
   }
   static void deleteArray_FemtoMcVertex(void *p) {
      delete [] ((::FemtoMcVertex*)p);
   }
   static void destruct_FemtoMcVertex(void *p) {
      typedef ::FemtoMcVertex current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FemtoMcVertex(TBuffer &buf, void *obj) {
      ((::FemtoMcVertex*)obj)->::FemtoMcVertex::Streamer(buf);
   }
} // end of namespace ROOT for class ::FemtoMcVertex

//______________________________________________________________________________
void FemtoMtdPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class FemtoMtdPidTraits.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FemtoDstBranch::Streamer(R__b);
      R__b >> mDeltaY;
      R__b >> mDeltaZ;
      R__b >> mDeltaTimeOfFlight;
      R__b >> mMatchFlag;
      R__b >> mMtdHitChan;
      R__b >> mTriggerFlag;
      R__b >> mIdTruth;
      R__b.CheckByteCount(R__s, R__c, FemtoMtdPidTraits::IsA());
   } else {
      R__c = R__b.WriteVersion(FemtoMtdPidTraits::IsA(), kTRUE);
      FemtoDstBranch::Streamer(R__b);
      R__b << mDeltaY;
      R__b << mDeltaZ;
      R__b << mDeltaTimeOfFlight;
      R__b << mMatchFlag;
      R__b << mMtdHitChan;
      R__b << mTriggerFlag;
      R__b << mIdTruth;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FemtoMtdPidTraits(void *p) {
      return  p ? new(p) ::FemtoMtdPidTraits : new ::FemtoMtdPidTraits;
   }
   static void *newArray_FemtoMtdPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::FemtoMtdPidTraits[nElements] : new ::FemtoMtdPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_FemtoMtdPidTraits(void *p) {
      delete ((::FemtoMtdPidTraits*)p);
   }
   static void deleteArray_FemtoMtdPidTraits(void *p) {
      delete [] ((::FemtoMtdPidTraits*)p);
   }
   static void destruct_FemtoMtdPidTraits(void *p) {
      typedef ::FemtoMtdPidTraits current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FemtoMtdPidTraits(TBuffer &buf, void *obj) {
      ((::FemtoMtdPidTraits*)obj)->::FemtoMtdPidTraits::Streamer(buf);
   }
} // end of namespace ROOT for class ::FemtoMtdPidTraits

//______________________________________________________________________________
void FemtoTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class FemtoTrack.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FemtoDstBranch::Streamer(R__b);
      R__b >> mPt;
      R__b >> mEta;
      R__b >> mPhi;
      R__b >> mId;
      R__b >> mDedx;
      R__b >> mNHitsFit;
      R__b >> mNHitsMax;
      R__b >> mNHitsDedx;
      R__b >> mNSigmaPion;
      R__b >> mNSigmaKaon;
      R__b >> mNSigmaProton;
      R__b >> mNSigmaElectron;
      R__b >> mDCA;
      R__b >> mBTofPidTraitsIndex;
      R__b >> mMtdPidTraitsIndex;
      R__b >> mEmcPidTraitsIndex;
      R__b >> mHelixIndex;
      R__b >> mMcIndex;
      R__b.CheckByteCount(R__s, R__c, FemtoTrack::IsA());
   } else {
      R__c = R__b.WriteVersion(FemtoTrack::IsA(), kTRUE);
      FemtoDstBranch::Streamer(R__b);
      R__b << mPt;
      R__b << mEta;
      R__b << mPhi;
      R__b << mId;
      R__b << mDedx;
      R__b << mNHitsFit;
      R__b << mNHitsMax;
      R__b << mNHitsDedx;
      R__b << mNSigmaPion;
      R__b << mNSigmaKaon;
      R__b << mNSigmaProton;
      R__b << mNSigmaElectron;
      R__b << mDCA;
      R__b << mBTofPidTraitsIndex;
      R__b << mMtdPidTraitsIndex;
      R__b << mEmcPidTraitsIndex;
      R__b << mHelixIndex;
      R__b << mMcIndex;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FemtoTrack(void *p) {
      return  p ? new(p) ::FemtoTrack : new ::FemtoTrack;
   }
   static void *newArray_FemtoTrack(Long_t nElements, void *p) {
      return p ? new(p) ::FemtoTrack[nElements] : new ::FemtoTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_FemtoTrack(void *p) {
      delete ((::FemtoTrack*)p);
   }
   static void deleteArray_FemtoTrack(void *p) {
      delete [] ((::FemtoTrack*)p);
   }
   static void destruct_FemtoTrack(void *p) {
      typedef ::FemtoTrack current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FemtoTrack(TBuffer &buf, void *obj) {
      ((::FemtoTrack*)obj)->::FemtoTrack::Streamer(buf);
   }
} // end of namespace ROOT for class ::FemtoTrack

//______________________________________________________________________________
void FemtoTrackHelix::Streamer(TBuffer &R__b)
{
   // Stream an object of class FemtoTrackHelix.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FemtoDstBranch::Streamer(R__b);
      R__b.ReadStaticArray((float*)mPar);
      R__b >> mMap0;
      R__b >> mMap1;
      R__b >> mDCA;
      R__b.CheckByteCount(R__s, R__c, FemtoTrackHelix::IsA());
   } else {
      R__c = R__b.WriteVersion(FemtoTrackHelix::IsA(), kTRUE);
      FemtoDstBranch::Streamer(R__b);
      R__b.WriteArray(mPar, 6);
      R__b << mMap0;
      R__b << mMap1;
      R__b << mDCA;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FemtoTrackHelix(void *p) {
      return  p ? new(p) ::FemtoTrackHelix : new ::FemtoTrackHelix;
   }
   static void *newArray_FemtoTrackHelix(Long_t nElements, void *p) {
      return p ? new(p) ::FemtoTrackHelix[nElements] : new ::FemtoTrackHelix[nElements];
   }
   // Wrapper around operator delete
   static void delete_FemtoTrackHelix(void *p) {
      delete ((::FemtoTrackHelix*)p);
   }
   static void deleteArray_FemtoTrackHelix(void *p) {
      delete [] ((::FemtoTrackHelix*)p);
   }
   static void destruct_FemtoTrackHelix(void *p) {
      typedef ::FemtoTrackHelix current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FemtoTrackHelix(TBuffer &buf, void *obj) {
      ((::FemtoTrackHelix*)obj)->::FemtoTrackHelix::Streamer(buf);
   }
} // end of namespace ROOT for class ::FemtoTrackHelix

namespace {
  void TriggerDictionaryInitialization_DictionaryFemtoDst_Impl() {
    static const char* headers[] = {
"FemtoBTofPidTraits.h",
"FemtoEvent.h",
"FemtoMcTrack.h",
"FemtoMcVertex.h",
"FemtoMtdPidTraits.h",
"FemtoTrack.h",
"FemtoTrackHelix.h",
"FemtoDstBranch.h",
0
    };
    static const char* includePaths[] = {
"/Users/jdb/bnl/work/upc/FemtoPairAnalysis/modules/FemtoDstFormat/",
"/Users/jdb/bnl/vendor/6.14.04/include",
"/Users/jdb/bnl/work/upc/FemtoPairAnalysis/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DictionaryFemtoDst dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$FemtoDstBranch.h")))  __attribute__((annotate("$clingAutoload$FemtoBTofPidTraits.h")))  FemtoDstBranch;
class __attribute__((annotate("$clingAutoload$FemtoBTofPidTraits.h")))  FemtoBTofPidTraits;
class __attribute__((annotate("$clingAutoload$FemtoEvent.h")))  FemtoEvent;
class __attribute__((annotate("$clingAutoload$FemtoMcTrack.h")))  FemtoMcTrack;
class __attribute__((annotate("$clingAutoload$FemtoMcVertex.h")))  FemtoMcVertex;
class __attribute__((annotate("$clingAutoload$FemtoMtdPidTraits.h")))  FemtoMtdPidTraits;
class __attribute__((annotate("$clingAutoload$FemtoTrack.h")))  FemtoTrack;
class __attribute__((annotate("$clingAutoload$FemtoTrackHelix.h")))  FemtoTrackHelix;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DictionaryFemtoDst dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "FemtoBTofPidTraits.h"
#include "FemtoEvent.h"
#include "FemtoMcTrack.h"
#include "FemtoMcVertex.h"
#include "FemtoMtdPidTraits.h"
#include "FemtoTrack.h"
#include "FemtoTrackHelix.h"
#include "FemtoDstBranch.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FemtoBTofPidTraits", payloadCode, "@",
"FemtoDstBranch", payloadCode, "@",
"FemtoEvent", payloadCode, "@",
"FemtoMcTrack", payloadCode, "@",
"FemtoMcVertex", payloadCode, "@",
"FemtoMtdPidTraits", payloadCode, "@",
"FemtoTrack", payloadCode, "@",
"FemtoTrackHelix", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DictionaryFemtoDst",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DictionaryFemtoDst_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DictionaryFemtoDst_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DictionaryFemtoDst() {
  TriggerDictionaryInitialization_DictionaryFemtoDst_Impl();
}
