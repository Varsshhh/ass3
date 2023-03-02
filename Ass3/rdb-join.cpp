#include<bits/stdc++.h>
#include "rdb.h"
using namespace std;

// Implementation of natural join operator
Relation* Relation::naturalJoin(Relation *r1, Relation *r2, list<string> joinattrs) 
{
    // Check if the join attributes are valid
    for (string s : joinattrs) {
        if (find(r1->getAttrNames().begin(), r1->getAttrNames().end(), s) == r1->getAttrNames().end() ||
            find(r2->getAttrNames().begin(), r2->getAttrNames().end(), s) == r2->getAttrNames().end()) {
            cout << "Join attributes are invalid" << endl;
            return nullptr;
        }
    }
    // Find matching attribute indices in each relation
    vector<int> attrind1, attrind2;
    vector<string> attrnames;
    for (const auto& attrname : joinattrs)
    {
        int ind1 = find(r1->getAttrNames().begin(), r1->getAttrNames().end(), attrname) - r1->getAttrNames().begin();
        int ind2 = find(r2->getAttrNames().begin(), r2->getAttrNames().end(), attrname) - r2->getAttrNames().begin();
        attrind1.push_back(ind1);
        attrind2.push_back(ind2);
        attrnames.push_back(attrname);
    }

    // Create a new relation with combined attribute names
    string newName = "NaturalJoin ("+r1->getName() + "," + r2->getName()+")";
    Relation* result = new Relation(newName, r1->getAttrNames(), r1->getAttrInds());
    vector<string> r2AttrNames = r2->getAttrNames();
    for (int i = 0; i < r2AttrNames.size(); ++i)
    {
        if (find(attrnames.begin(), attrnames.end(), r2AttrNames[i]) == attrnames.end())
        {
            result->addAttr(r2AttrNames[i]);
            result->addAttrInd(r1->nattrs() + i);
        }

    }

    // Join the records with matching attribute values
    for (const auto& rec1 : r1->getRecords())
    {
        for (const auto& rec2 : r2->getRecords())
        {
            bool match = true;
            for (int i = 0; i < attrind1.size(); ++i)
            {
                if (*(rec1->getAttrbyindex(attrind1[i])) != *(rec2->getAttrbyindex(attrind2[i])))
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                Record* newRec = new Record();
                for (int i = 0; i < rec1->size(); ++i)
                {
                    newRec->pushAttr(rec1->getAttrbyindex(i)->clone());
                }
                for (int i = 0; i < rec2->size(); ++i)
                {
                    if (find(attrind2.begin(), attrind2.end(), i) == attrind2.end())
                    {
                        newRec->pushAttr(rec2->getAttrbyindex(i)->clone());
                    }
                }
                result->addRecord(newRec);
            }
        }
    }

    return result;
}
