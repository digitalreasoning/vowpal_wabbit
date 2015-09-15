#include "search_java_task.h"
#include "../java/src/main/c++/vw_VW.h"
#include <jni.h>

extern JNIEnv java_environment;

namespace JavaTask {
  Search::search_task task = { "java", run, initialize, finish, run_setup, run_takedown};
  jobject java_search_task;
  jclass java_search_class;

  void initialize(Search::search& sch, size_t& num_actions, po::variables_map& vm) {
    jobect jSearch = createJavaSearchFromPointer(sch);
    java_search_task = instantiate_java_search_task(vm);
    jmethodID initialize_method_id = java_environment->GetMethodId(java_search_class, "initialize", "(Lvw.search.Search;ILjava.util.Map;)V");
    // TODO: add handling passing of variable map to initialize
    java_environment->CallVoidMethod(java_environment, java_search_task, initialize_method_id, jSearch, num_actions, null);
    return;
  }

  jclass instantiate_java_search_task(po::variables_map& vm)
  {
    string java_class_name_with_dots = vm.get("search_java_class");
    char* java_class_name_with_slashes = replace_dots_with_slashes(java_class_name_with_dots);
    java_search_class = (*java_environment)->FindClass(java_environment, java_class_name_with_slashes);
    jmethodID java_search_task_constructor = java_environment->GetMethodID(java_class, "<init>", "()V");
    return java_environment->NewObject(java_search_class, java_search_task_constructor);
  }

  char* replace_dots_with_slashes(char* name) {
    char * new_name = new char[strlen(name)+1];

    int n=0;
    while (*name != '\0')
    {
      char c = *name;
      if (c == '.')
      {
        new_name[n] = '/';
      }
      else
      {
        new_name[n] = c;
      }
      n++;
    }
    return new_name;
  }


  void finish(Search::search& sch) {
    jobject jSearch = createJavaSearchFromPointer(sch);
    jobject jexamples =  create_java_example_array_from_c_vector(ec);
    jmethodID methodID = java_environment->GetMethodId(java_search_class, method_name, "(Lvw.search.Search)V");
    java_environment->CallVoidMethod(java_environment, methodID, jSearch);
  }

  void run(Search::search& sch, vector<example*>& ec) {
    call_method_id_by_name("run", sch, ec);
  }

  void run_setup(Search::search& sch, vector<example*>& ec) {
    call_method_id_by_name("runSetup", sch, ec);
  }


  void run_takedown(Search::search& sch, vector<example*>& ec) {
    call_method_id_by_name("runTakedown", sch, ec);
  }

  void call_method_id_by_name(char* method_name, Search::search& sch, vector<example*>& ec) {
    jobject jSearch = createJavaSearchFromPointer(sch);
    jobject jexamples =  create_java_example_array_from_c_vector(ec);
    jmethodID methodID = java_environment->GetMethodId(java_search_class, method_name, "(Lvw.search.Search;[Lvw.search.Example;)V");
    java_environment->CallVoidMethod(java_environment, methodID, jSearch, jexamples);
    return;
  }

    jobject createJavaSearchFromPointer(Search::search& sch){
      jlong schPtr = (jlong) *sch;
      java_search_class = (*java_environment)->FindClass(java_environment, "vw.search.Search");
      jmethodID java_search_constructor = java_environment->GetMethodID(java_class, "<init>", "(L)V");
      return java_environment->NewObject(java_search_class, java_search_constructor, schPtr);
    }

}


namespace JavaTask {
  Search::search_task task = { "java", run, initialize, finish, run_setup, run_takedown  };
}


search_java_task::search_java_task()
{
}
