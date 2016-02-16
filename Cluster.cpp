//
// Created by Gavin on 2/14/2016.
//

#include "Cluster.h"

namespace Clustering {

    LNode::LNode(const Point &p, LNodePtr n) : point(p) {
        next = n;
    }

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
            __points = new LNode(p, nullptr);
        }
        else { // Non-empty list
            // Make sure point does not already exist
            if (contains(p))
                return; // Point already exists, exit

            // next and previous pointers
            LNodePtr next;
            LNodePtr prev;

            next = __points;    // Start of list
            prev = nullptr;

            // find insert position
            while (next != nullptr) {
                if (p < next->point) {
                    // Insert here
                    if (prev == nullptr) {
                        // First element in list
                        __points = new LNode(p, next);

                        ++__size;

                        return;  // Add complete, exit
                    }
                    else {
                        // Not first element in list
                        prev->next = new LNode(next->point, next->next);

                        ++__size;

                        return;  // Add complete, exit
                    }
                }

                prev = next;
                next = next->next;

            }

            // No insert found, add to end
            prev->next = new LNode(p, next->next);

            ++__size;
        }
    }

    const Point &Cluster::remove(const Point &p) {
        if (contains(p)) {
            // Point is in list
            LNodePtr next;
            LNodePtr prev = nullptr;

            next = __points;

            while (next != nullptr) {
                if (next->point == p) {
                    // Found point
                    if (prev == nullptr) {
                        // First element
                        __points = next->next;

                        delete next;
                        
                        break;
                    }
                    else {
                        // not first
                        prev->next = next->next;
                        delete next;

                        break;
                    }
                }

                prev = next;
                next = next->next;
            }
        }

        return p;
    }

    bool Cluster::contains(const Point &p) {
        LNodePtr next = __points;

        while (next != nullptr) {
            //  Check if ID's of the pointers match
            if (next->point.getId() == p.getId())
                return true;    // True, contains point
            else
                next = next->next;
        }

        // End of loop, does not contain point
        return false;
    }
}