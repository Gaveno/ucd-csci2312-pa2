//
// Created by Gavin on 2/14/2016.
//

#include "Cluster.h"

namespace Clustering {

    Cluster::Cluster() {
        __size = 0;
        __points = nullptr;
    }

    int Cluster::getSize() const {
        return __size;
    }

    // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const Point &p) {
        // Empty list, adding first
        if (__size == 0) {
            ++__size;
            __points = new LNode;
            __points->next = nullptr;
            __points->point = p;
        }
        else { // Non-empty list
            // next and previous pointers
            LNodePtr next;
            LNodePtr prev;

            next = __points;
            prev = nullptr;

            // find insert position
            while (next != nullptr) {
                if (p < next->point) {
                    // Insert here
                    if (prev == nullptr) {
                        // First element in list
                        __points = new LNode;
                        __points->next = next;
                        __points->point = p;

                        ++__size;

                        return;  // Add complete, exit
                    }
                    else {
                        // Not first element in list
                        prev->next = new LNode;
                        prev->next->next = next;

                        prev->next->point = p;

                        ++__size;

                        return;  // Add complete, exit
                    }
                }

                prev = next;
                next = next->next;

            }

            // No insert found, add to end
            prev->next = new LNode;
            prev->next->next = nullptr;

            prev->next->point = p;

            ++__size;
        }
    }
    
    const Point &Cluster::remove(const Point &);
    bool Cluster::contains(const Point &);
}