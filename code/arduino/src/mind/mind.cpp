#include "mind.h"

static bool _work;

bool Mind::in_rest() {
    return !_work;
}

void Mind::stop_work() {
    _work = false;
}

void Mind::start_work() {
    _work = true;
}