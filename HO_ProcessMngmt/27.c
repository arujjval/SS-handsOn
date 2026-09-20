#include <stdio.h>
#include <sched.h> // related to CPU scheduling

// Higher priority -> Higher preference
// Real-time scheduling policies: processes needing more predictable 
// scheduling, important ones where time matters

int main() {
    int min_priority;
    int max_priority;

    // min and max priority allowed for this scheduling policy
    // SCHED_FIFO: first in, first out scheduling policy, type of
    // real-time scheduling
    min_priority = sched_get_priority_min(SCHED_FIFO);
    max_priority = sched_get_priority_max(SCHED_FIFO);

    printf("Minimum real-time priority: %d\n", min_priority);
    printf("Maximum real-time priority: %d\n", max_priority);

    return 0;
}