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
    {int i,j;
        for(i=0;i<(r1->nattrs_);i++) {
            if((r1->getAttrNames())[i]==attrname) break;

        }
        int ind1=i;
        

         for(j=0;j<(r2->nattrs_);j++) {
            if((r2->getAttrNames())[j]==attrname) break;

        }
        int ind2=j;
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
        int k=0;

        for(auto &name:attrnames){
            if(name!=r2AttrNames[i]) k++;
        }
        




        if (k==(attrnames).size())
        {
            int j1=0;
            
            result->addAttr(r2AttrNames[i]);
            result->addAttrInd(r1->nattrs() + j1);
            j1++;
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
                    Attr* ptr= rec1->getAttrbyindex(i);
                    if(ptr->getValue()=="int"){
                        int value;

                        IntAttr* p1=dynamic_cast<IntAttr*>(ptr);value=p1->getValue();
                        
                        IntAttr *clone=new IntAttr(value);
                        newRec->pushAttr(clone);
                    }
                     else if(ptr->getValue()=="float"){
                        float value;

                        FloatAttr* p1=dynamic_cast<FloatAttr*>(ptr);value=p1->getValue();
                        
                        FloatAttr *clone=new FloatAttr(value);
                        newRec->pushAttr(clone);
                    }
                    else {
                        string value;

                        StringAttr* p1=dynamic_cast<StringAttr*>(ptr);value=p1->getValue();
                        
                       StringAttr *clone=new StringAttr(value);
                       newRec->pushAttr(clone);
                    }


                 }

                    

                
                for (int i = 0; i < rec2->size(); ++i)
                {
                    if (find(attrind2.begin(), attrind2.end(), i) == attrind2.end())
                    {
                             Attr* ptr= rec2->getAttrbyindex(i);
                                if(ptr->getValue()=="int"){
                        int value;

                        IntAttr* p1=dynamic_cast<IntAttr*>(ptr);value=p1->getValue();
                        
                        IntAttr *clone=new IntAttr(value);
                        newRec->pushAttr(clone);
                    }
                     else if(ptr->getValue()=="float"){
                        float value;

                        FloatAttr* p1=dynamic_cast<FloatAttr*>(ptr);value=p1->getValue();
                        
                        FloatAttr *clone=new FloatAttr(value);
                        newRec->pushAttr(clone);
                    }
                    else {
                        string value;

                        StringAttr* p1=dynamic_cast<StringAttr*>(ptr);value=p1->getValue();
                        
                       StringAttr *clone=new StringAttr(value);
                       newRec->pushAttr(clone);
                    }






                        // newRec->pushAttr(rec2->getAttrbyindex(i)->clone());
                    }
                }
                result->addRecord(newRec);
                // Record* newRec = new Record();
                // for (int i = 0; i < rec1->size(); ++i)
                // {
                //     newRec->pushAttr(rec1->getAttrbyindex(i)->clone());
                // }
                // for (int i = 0; i < rec2->size(); ++i)
                // {
                //     if (find(attrind2.begin(), attrind2.end(), i) == attrind2.end())
                //     {
                //         newRec->pushAttr(rec2->getAttrbyindex(i)->clone());
                //     }
                // }
                // result->addRecord(newRec);
            }
        }
    }

    return result;
}