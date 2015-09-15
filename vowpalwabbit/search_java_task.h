#ifndef SEARCH_JAVA_TASK_H
#define SEARCH_JAVA_TASK_H

#pragma once
#include "search.h"

namespace JavaTask {
    void initialize(Search::search&, size_t&, po::variables_map&);
    void finish(Search::search&);
    void run(Search::search&, vector<example*>&);
    void run_setup(Search::search&, vector<example*>&);
    void run_takedown(Search::search&, vector<example*>&);
    extern Search::search_task task;
}



#endif // SEARCH_JAVA_TASK_H
