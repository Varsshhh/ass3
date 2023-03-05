#include <bits/stdc++.h>
#include "rdb.h"
using namespace std;

// 1. Union: All records of both R1 and R2.
Relation *union_(Relation *R1, Relation *R2)
{ // Check if the schemas are the same
    if (R1->getAttrNames() != R2->getAttrNames())
    {
        cerr << "Error: Cannot perform union operation on relations with different schemas\n";
        return nullptr;
    }

    Relation *result = new Relation();
    result->setName("Union (" + R1->getName() + " , " + R2->getName() + ")"); // Use the name of the first relation

    // Add attribute names and indices
    result->setAttrNames(R1->getAttrNames());
    result->setAttrInds(R1->getAttrInds());

    // Add records from R1
    for (Record *rec : R1->getRecords())
    {
        result->addRecord(new Record(*rec));
    }

    // Add records from R2 that are not already in R1
    for (Record *rec : R2->getRecords())
    {
        bool found = false;
        for (Record *r : result->getRecords())
        {
            if (*r == *rec)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            result->addRecord(new Record(*rec));
        }
    }
    return result;
}

// 2. Difference: Records in R1 but not in R2.
Relation *difference(Relation *R1, Relation *R2)
{ // Check if R1 and R2 have the same schema
    if (R1->getAttrNames() != R2->getAttrNames() || R1->getAttrInds() != R2->getAttrInds())
    {
        cout << "Error: schemas of R1 and R2 are not the same." << endl;
        return nullptr;
    }

    // Create a new relation with the same schema as R1 and R2
    vector<string> attrnames = R1->getAttrNames();
    vector<int> attrinds = R1->getAttrInds();
    string name = "Difference (" + R1->getName() + " , " + R2->getName() + ")";
    Relation *result = new Relation(name, attrnames, attrinds);

    // Add records from R1 that are not in R2
    for (Record *rec : R1->getRecords())
    {
        bool found = false;
        for (Record *r : R2->getRecords())
        {
            if (*r == *rec)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            result->addRecord(new Record(*rec));
        }
    }

    return result;
}

// 3. Cartesian Product: All possible pairs of records from R1 and R2.
Relation *cartesianProduct(Relation *r1, Relation *r2)
{
    // Create a new relation
    Relation *res = new Relation();

    // Set the name of the new relation to the concatenation of the names of r1 and r2
    res->setName("CartesianProduct (" + r1->getName() + " , " + r2->getName() + ")");

    // Set the attribute names and indices of the new relation
    vector<string> attrnames;
    vector<int> attrinds;
    for (int i = 0; i < r1->nattrs(); i++)
    {
        attrnames.push_back(r1->getAttrNames()[i]);
        attrinds.push_back(i);
    }
    for (int i = 0; i < r2->nattrs(); i++)
    {
        attrnames.push_back(r2->getAttrNames()[i]);
        attrinds.push_back(i + r1->nattrs());
    }
    res->setAttrNames(attrnames);
    res->setAttrInds(attrinds);

    // Add the cartesian product of the records of r1 and r2 to the new relation
    for (auto r1rec : r1->getRecords())
    {
        for (auto r2rec : r2->getRecords())
        {
            vector<Attr *> attrs;
            for (auto attr : r1rec->getAttr())
            {
                attrs.push_back(attr);
            }
            for (auto attr : r2rec->getAttr())
            {
                attrs.push_back(attr);
            }
            Record *rec = new Record(attrs);
            res->addRecord(rec);
        }
    }

    return res;
}

// 4. Projection: New relation with a subset of columns.
Relation *projection(Relation *r1, list<string> projectattrs)
{
    vector<int> projIndices;
    for (auto attrName : projectattrs)
    {
        auto it = find(r1->getAttrNames().begin(), r1->getAttrNames().end(), attrName);
        if (it == r1->getAttrNames().end())
        {
            cerr << "Error: Attribute " << attrName << " not found in relation.\n";
            return nullptr;
        }
        int index = distance(r1->getAttrNames().begin(), it);
        projIndices.push_back(index);
    }

    vector<string> projAttrNames;
    for (auto index : projIndices)
    {
        projAttrNames.push_back(r1->getAttrNames()[index]);
    }

    vector<int> projAttrInds;
    for (auto index : projIndices)
    {
        projAttrInds.push_back(r1->getAttrInds()[index]);
    }

    Relation *projRelation = new Relation("Projection(" + r1->getName() + ")", projAttrNames, projAttrInds);

    for (auto rec : r1->getRecords())
    {
        vector<Attr *> projAttrs;
        for (auto index : projIndices)
        {
            projAttrs.push_back(rec->getAttrbyindex(index));
        }
        projRelation->addRecord(new Record(projAttrs));
    }

    return projRelation;
}

// 5. Selection: New relation with a subset of records matching a boolean expression in DNF form.
Relation *selection(Relation *r1, DNFformula *f)
{ // Create a new relation with the same schema as the input relation
    vector<string> attrnames = r1->getAttrNames();
    vector<int> attrinds = r1->getAttrInds();
    Relation *result = new Relation("Selection(" + r1->getName() + ")", attrnames, attrinds);

    // Iterate through each record in the relation
    for (Record *rec : r1->getRecords())
    {
        bool satisfiesDNF = false;

        // Check if the record satisfies the DNF formula
        for (list<tuple<string, char, Attr *>> conjuncts : f->ops)
        {
            bool satisfiesCNF = true;

            // Check if the record satisfies the CNF conjunction
            for (tuple<string, char, Attr *> conjunct : conjuncts)
            {
                string attrname = get<0>(conjunct);
                char op = get<1>(conjunct);
                Attr *value = get<2>(conjunct);

                // Find the index of the attribute
                int attrindex = -1;
                for (int i = 0; i < attrnames.size(); i++)
                {
                    if (attrnames[i] == attrname)
                    {
                        attrindex = i;
                        break;
                    }
                }
                if (attrindex == -1)
                {
                    cerr << "Error: Attribute " << attrname << " not found." << endl;
                    return nullptr;
                }

                // Check the comparison operator and apply the comparison
                Attr *recordAttr = rec->getAttrbyindex(attrindex);
                if (recordAttr == nullptr)
                {
                    cerr << "Error: Record attribute is null." << endl;
                    return nullptr;
                }

                bool comparisonResult = false;
                if (op == '=')
                {
                    comparisonResult = (*value == *recordAttr);
                }
                else if (op == '<')
                {
                    comparisonResult = (*recordAttr < *value);
                }
                else if (op == '>')
                {
                    comparisonResult = (*recordAttr > *value);
                }
                else if (op == 'l')
                {
                    comparisonResult = (*recordAttr <= *value);
                }
                else if (op == 'g')
                {
                    comparisonResult = (*recordAttr >= *value);
                }
                else if (op == 'n')
                {
                    comparisonResult = (*value != *recordAttr);
                }
                else
                {
                    cerr << "Error: Invalid comparison operator: " << op << endl;
                    return nullptr;
                }

                satisfiesCNF &= comparisonResult;
            }

            satisfiesDNF |= satisfiesCNF;
            if (satisfiesDNF)
            {
                break;
            }
        }

        // If the record satisfies the DNF formula, add it to the result relation
        if (satisfiesDNF)
        {
            result->addRecord(new Record(*rec));
        }
    }

    return result;
}

// 6. Rename: rename an attribute in schema
Relation *rename_(Relation *r1, string s1, string s2)
{
    vector<string> attrnames = r1->getAttrNames();
    for (int i = 0; i < attrnames.size(); i++)
    {
        if (attrnames[i] == s1)
        {
            attrnames[i] = s2;
        }
    }
    r1->setAttrNames(attrnames);
    return r1;
}

Relation *naturalJoin(Relation *r1, Relation *r2, list<string> joinattrs)
{
    // Check if the join attributes are valid
    for (string s : joinattrs)
    {
        if (find(r1->getAttrNames().begin(), r1->getAttrNames().end(), s) == r1->getAttrNames().end() ||
            find(r2->getAttrNames().begin(), r2->getAttrNames().end(), s) == r2->getAttrNames().end())
        {
            cout << "Join attributes are invalid" << endl;
            return nullptr;
        }
    }
    // Find matching attribute indices in each relation
    vector<int> attrind1, attrind2;
    vector<string> attrnames;
    for (const auto &attrname : joinattrs)
    {
        int ind1 = find(r1->getAttrNames().begin(), r1->getAttrNames().end(), attrname) - r1->getAttrNames().begin();
        int ind2 = find(r2->getAttrNames().begin(), r2->getAttrNames().end(), attrname) - r2->getAttrNames().begin();
        attrind1.push_back(ind1);
        attrind2.push_back(ind2);
        attrnames.push_back(attrname);
    }

    // Create a new relation with combined attribute names
    string newName = "NaturalJoin (" + r1->getName() + "," + r2->getName() + ")";
    Relation *result = new Relation(newName, r1->getAttrNames(), r1->getAttrInds());
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
    for (const auto &rec1 : r1->getRecords())
    {
        for (const auto &rec2 : r2->getRecords())
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
                Record *newRec = new Record();
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

int main()
{
    map<string, Relation *> relationmap; // map to store all created relationmap
    string input;
    while (true)
    {
        int choice;
        cout << "Enter the type of operation to perform:\n"
             << "10. Create new table\n"
             << "11. Delete table\n"
             << "12. Add a record to table\n"
             << "13. Print a table\n"
             << "1. Union\n"
             << "2. Difference\n"
             << "3. Cartesian Product\n"
             << "4. Projection\n"
             << "5. Selection\n"
             << "6. Rename\n"
             << "7. Natural Join\n"
             << "9. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 10:
        { // create new table
            string relname;
            cout << "enter relation name" << endl;
            cin >> relname;
            int n;
            cout << "enter number of attributes" << endl;
            cin >> n;
            vector<string> attrNames(n);
            vector<int> attrInds(n);
            cout << "enter n attributes" << endl;
            for (int i = 0; i < n; i++)
            {
                cin >> attrNames[i];
                attrInds[i] = i;
            }
            Relation *rel = new Relation(relname, attrNames, attrInds);
            relationmap[relname] = rel;
            cout << "Table " << relname << " created." << endl;
            break;
        }
        case 11:
        { // delete a table

            string relname;
            cout << "enter relation name" << endl;
            cin >> relname;
            if (relationmap.count(relname))
            {
                delete relationmap[relname];
                relationmap.erase(relname);
                cout << "Table " << relname << " deleted." << endl;
            }
            else
            {
                cout << "Table " << relname << " does not exist." << endl;
            }
            break;
        }
        case 12:
        { // add record to a table
            string relname;
            cout << "enter relation name" << endl;
            cin >> relname;
            if (!relationmap.count(relname))
            {
                cout << "Table " << relname << " does not exist." << endl;
                continue;
            }
            int n = relationmap[relname]->nattrs();
            vector<Attr *> attrs(n);
            vector<string> attrtypes(n);
            vector<string> attrnames = relationmap[relname]->getAttrNames();

            for (int i = 0; i < n; i++)
            {
                cout << "Enter the type of attribute for " << attrnames[i] << ": ";
                cin >> attrtypes[i];
                cout << endl;
            }

            for (int i = 0; i < n; i++)
            {
                string value;
                cout << "Enter the value of attribute for " << attrnames[i] << ": ";
                cin >> value;
                if (attrtypes[i] == "int")
                {
                    attrs.push_back(new IntAttr(stoi(value))); 
                }
                else if (attrtypes[i] == "float")
                {
                    attrs.push_back(new FloatAttr(stof(value)));
                }
                else if (attrtypes[i] == "string")
                {
                    attrs.push_back(new StringAttr(value));
                }
                else
                {
                    cout << "no attribute type found" << endl;
                }
            }
            Record *rec = new Record(attrs);
            relationmap[relname]->addRecord(rec);
            cout << "Record added successfully.\n";
            break;
        }
        case 13:
        {
            // // Function to print a table

            // string relName;
            // cout << "Enter the name of the relation to print: ";
            // cin >> relName;
            // if (relationmap.find(relName) == relationmap.end())
            // {
            //     cout << "Error: relation does not exist.\n";
            //     break;
            // }
            // cout << relationmap[relName];
        //     string relName;
        // cout << "Enter the name of the relation to print: ";
        // cin >> relName;
        // if (relationmap.find(relName) == relationmap.end()) {
        //     cout << "Error: relation does not exist.\n";
        //     break;
        // }
        // Relation *relPtr = relationmap[relName];
        // cout << "Relation " << relPtr->getName() << endl;
        // vector<string> attrnames = relPtr->getAttrNames();
        // for (int i = 0; i < attrnames.size(); i++) {
        //     cout << attrnames[i] << "\t";
        // }
        // cout << endl;
        // list<Record*> recs = relPtr->getRecords();
        // for (auto it = recs.begin(); it != recs.end(); it++) {
        //     Record* record = *it;
        //     vector<Attr*> attrs = record->getAttr();
        //     for (int j = 0; j < attrs.size(); j++) {
        //         cout << attrs[j] << "\t";
        //     }
        //     cout << endl;

            string relName;
            cout << "Enter the name of the relation to print: ";
            cin >> relName;
            if (relationmap.find(relName) == relationmap.end())
            {
                cout << "Error: relation does not exist.\n";
                break;
            }
            Relation* rel = relationmap[relName];
            rel->printrelation();
          
           break;
        }

        case 1:
        {
            string relName1, relName2;
            cout << "Enter the name of the first relation: ";
            cin >> relName1;
            cout << "Enter the name of the second relation: ";
            cin >> relName2;
            if (relationmap.find(relName1) == relationmap.end() ||
                relationmap.find(relName2) == relationmap.end())
            {
                cout << "Error: relation does not exist.\n";
                break;
            }
            Relation *newRel = union_(relationmap[relName1], relationmap[relName2]);
            relationmap[newRel->getName()] = newRel;
            break;
        }
        case 2:
        {
            string relName1, relName2;
            cout << "Enter the name of the first relation: ";
            cin >> relName1;
            cout << "Enter the name of the second relation: ";
            cin >> relName2;
            if (relationmap.find(relName1) == relationmap.end() ||
                relationmap.find(relName2) == relationmap.end())
            {
                cout << "Error: relation does not exist.\n";
                break;
            }
            Relation *newRel = difference(relationmap[relName1], relationmap[relName2]);
            relationmap[newRel->getName()] = newRel;
            break;
        }
        case 3:
        {
            string relName1, relName2;
            cout << "Enter the name of the first relation: ";
            cin >> relName1;
            cout << "Enter the name of the second relation: ";
            cin >> relName2;
            if (relationmap.find(relName1) == relationmap.end() ||
                relationmap.find(relName2) == relationmap.end())
            {
                cout << "Error: relation does not exist.\n";
                break;
            }
            Relation *newRel = cartesianProduct(relationmap[relName1], relationmap[relName2]);
            relationmap[newRel->getName()] = newRel;
            break;
        }
        case 4:
        {
            string relName1;
            list<string> attrs;
            cout << "Enter the name of the relation: ";
            cin >> relName1;
            if (relationmap.find(relName1) == relationmap.end())
            {
                cout << "Error: relation does not exist.\n";
                break;
            }
            int numAttrs;
            cout << "Enter the number of attributes to project: ";
            cin >> numAttrs;
            for (int i = 0; i < numAttrs; i++)
            {
                string attrName;
                cout << "Enter attribute name: ";
                cin >> attrName;
                attrs.push_back(attrName);
            }
            Relation *newRel = projection(relationmap[relName1], attrs);
            cout << "New relation created: " << newRel->getName() << endl;
            relationmap[newRel->getName()] = newRel;
            break;
        }
        case 5: // Selection
        {
            // cout << "Enter relation name: ";
            // string relName;
            // cin >> relName;
            // cout << "Enter boolean expression (in DNF form): ";
            // DNFformula f;
            // readDNF(f);
            // Relation *newRel = rdbSelection(relationmap[relName], &f);
            // cout << "New relation created: " << newRel->getName() << endl;
            // relationmap[newRel->getName()] = newRel;
            // break;
        }
        case 6: // Rename
        {
            cout << "Enter relation name: ";
            string relName;
            cin >> relName;
            cout << "Enter old attribute name: ";
            string oldAttrName;
            cin >> oldAttrName;
            cout << "Enter new attribute name: ";
            string newAttrName;
            cin >> newAttrName;
            Relation *newRel = rename_(relationmap[relName], oldAttrName, newAttrName);
            cout << "New relation created: " << newRel->getName() << endl;
            relationmap[newRel->getName()] = newRel;
            break;
        }
        case 7: // Natural Join
        {
            cout << "Enter first relation name: ";
            string relName1;
            cin >> relName1;
            cout << "Enter second relation name: ";
            string relName2;
            cin >> relName2;
            cout << "Enter join attribute names (separated by spaces): ";
            list<string> joinAttrs;
            string attrName;
            while (cin >> attrName)
            {
                joinAttrs.push_back(attrName);
            }
            Relation *newRel = naturalJoin(relationmap[relName1], relationmap[relName2], joinAttrs);
            cout << "New relation created: " << newRel->getName() << endl;
            relationmap[newRel->getName()] = newRel;
            break; 
        }
        case 9: // Exit
        {
            cout << "Exiting..." << endl;
            exit(0);
        }
        default:
        {
            cout << "Invalid option." << endl;
            break;
        }
        }
    }
    return 0;
}


// ostream& operator<<(ostream &os, Attr* attr){
//     if(attr->dtype=="int") {IntAttr* p1=dynamic_cast<IntAttr*>(attr);os<<p1->getValue();}
//     else if(attr->dtype=="float"){ FloatAttr* p1=dynamic_cast<FloatAttr*>(attr);os<<p1->getValue();}
//     else { StringAttr* p1=dynamic_cast <StringAttr*> (attr);os<<p1->getValue();}
//     return os;

// }

// ostream &operator<<(ostream &os, Relation* r){
//     os << r->getName() << "\n";
//     for (int i = 0; i < r->nattrs(); ++i){
//         os << r->getAttrNames()[i] << " ";
//     }
//     os << "\n";
//     for(auto rec : r->getRecords()){
//         os<<(rec)<<"\n";
//     }
//     return os;
// }


// // ostream &operator<<(ostream &os, Record* record)
// // {
// //     for ( auto attr : record->getAttr())
// //     {
// //         os << attr << " ";
// //     }
// //     return os;
// // }
// ostream& operator<<(ostream &os, Record* record) {
//     for(auto attr: record->getAttr()) {
//         os<<attr<<" ";
//     }
//     return os;
// }