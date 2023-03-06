#include <bits/stdc++.h>
#include "rdb.h"
using namespace std;

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
        int j;
        int v1;float v2;string v3;
            string relname;
            cout << "enter relation name" << endl;
            cin >> relname;
            if (!relationmap.count(relname))
            {
                cout << "Table " << relname << " does not exist." << endl;
                continue;
            }
            int n = relationmap[relname]->nattrs();
            vector<Attr *> attrs;
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
                // cin >> value;
                if (attrtypes[i] == "int")
                {   
                    cin>>v1;
                    attrs.push_back(new IntAttr(v1)); 
                }
                else if (attrtypes[i] == "float")
                {
                    cin>>v2;
                    attrs.push_back(new FloatAttr(v2));
                }
                else if (attrtypes[i] == "string")
                {
                    cin>>v3;
                    attrs.push_back(new StringAttr(v3));
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
            cout<<endl;
            rel->printrelation();
            cout<<endl;
          
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
            string relname;
                cout<<"Enter the relation for which DNF is to be applied"<<endl;
                cin>>relname;

                cout << "Enter the number of disjunctions:"<<endl;
                int numb_disjun,temp_conjun;
                cin>>numb_disjun;

                DNFformula DNF;

                string attr_name,data_type;
                char comp_type;
                Attr* input_value;

                int int_input;
                float float_input;
                string string_input;

                for(int i=0;i<numb_disjun;i++)
                {
                    list<tuple<string, char, Attr *>> temp;
                    cout<<"Enter the number of conjunctions in disjunction no."<<i+1<<endl;
                    cin>>temp_conjun;

                    for(int j=0;j<temp_conjun;j++)
                    {
                        cout<<"comparison data no."<<j+1<<endl;
                        cout<<"Name of the attribute: "<<endl;
                        cin>>attr_name;
                        cout<<"Enter the datatype of the attribute (int/string/float)";
                        cin>>data_type;

                        if(data_type=="int")
                        {
                            cout<<"Enter the comparison operator"<<endl;
                            cin>>comp_type;
                            cout<<"Enter the attribute value"<<endl;
                            cin>>int_input;
                            input_value = new IntAttr(int_input);
                        }
                        else if(data_type=="float")
                        {
                            cout<<"Enter the comparison operator"<<endl;
                            cin>>comp_type;
                            cout<<"Enter the attribute value"<<endl;
                            cin>>float_input;
                            input_value = new FloatAttr(float_input);
                        }
                        else
                        {
                            cout<<"Enter the comparison operator"<<endl;
                            cin>>comp_type;
                            cout<<"Enter the attribute value"<<endl;
                            cin>>string_input;
                            input_value = new StringAttr(string_input);
                        }

                        //cin>>input_value;

                        temp.push_back(make_tuple(attr_name,comp_type,input_value));
                    }

                    DNF.ops.push_back(temp);
                }

                Relation * selection_rel;
                selection_rel = selection(relationmap[relname],&DNF);

                cout<<"Relation after selection created"<<endl;
                selection_rel->setName("selection_relation");
                relationmap["selection_relation"] = selection_rel;

                selection_rel->printrelation();
                break;

            
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