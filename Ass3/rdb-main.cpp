#include <bits/stdc++.h>
#include "rdb.h"
using namespace std;

int main()
{
    map<string, Relation *> relationmap; // map to store all created relationmap
    string input;
    while (true)
    {
        cout << "Enter command: ";
        getline(cin, input);
        if (input == "exit")
            break; // exit program
        else if (input == "list")
        { // list all created relationmap
            for (auto const &rel : relationmap)
            {
                cout << rel.first << endl;
            }
        }
        else if (input.substr(0, 6) == "create")
        { // create new table
            string relname;
            cout<<"enter relation name"<<endl;
            cin>>relname;
            int n;
            cout<<"enter number of attributes"<<endl;
            cin>>n;
            vector<string> attrNames(n);
            vector<int> attrInds(n);
            cout<<"enter n attributes"<<endl;
            for (int i = 0; i < n; i++)
            {
                cin>>attrNames[i];
                attrInds[i]=i;
            }
            Relation *rel = new Relation(relname,attrNames,attrInds);
            relationmap[relname] = rel;
            cout << "Table " << relname << " created." << endl;
        }
        else if (input.substr(0, 6) == "delete")
        { // delete a table

            string relname;
            cout<<"enter relation name"<<endl;
            cin>>relname;
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
        }
        else if (input.substr(0, 3) == "add")
        { // add record to a table
            string relname;
            cout<<"enter relation name"<<endl;
            cin>>relname;
            if (!relationmap.count(relname))
            {
                cout << "Table " << relname << " does not exist." << endl;
                continue;
            }
            int n=relationmap[relname]->nattrs();
            vector<Attr *> attrs(n);
            vector<string>attrtypes(n);
            vector<string>attrnames=relationmap[relname]->getAttrNames();

            for (int i = 0; i < n; i++)
            {
                cout<<"Enter the type of attribute for "<<attrnames[i]<<": ";
                cin>>attrtypes[i];
                cout<<endl;
            }
            

            for (int i = 0; i < n; i++)
            {
                string value;
                cout<<"Enter the value of attribute for "<<attrnames[i]<<": ";
                cin>>value;
                if (attrtypes[i]=="int"){attrs.push_back(new IntAttr(stoi(value)));}
                else if (attrtypes[i]=="float"){attrs.push_back(new IntAttr(stoi(value)));}
                else if (attrtypes[i]=="string"){attrs.push_back(new IntAttr(stoi(value)));}
                else{cout<<"no attribute type found"<<endl;}


            }
            Record* rec= new Record(attrs);
            relationmap[relname]->addRecord(rec);
            cout << "Record added successfully.\n";
        }
        else if (input.substr(0, 5) == "print"){
        // Function to print a table

            string relName;
            cout << "Enter the name of the relation to print: ";
            cin >> relName;
            if (relationmap.find(relName) == relationmap.end())
            {
                cout << "Error: relation does not exist.\n";
                return 0;
            }
            cout<<relationmap[relName];
        }
        // Function to create a new table using basic operators
        else if (input.substr(0, 9) == "operation"){
            string relName;
            cout << "Enter a name for the new relation: ";
            cin >> relName;
            if (relationmap.find(relName) != relationmap.end())
            {
                cout << "Error: relation already exists.\n";
                return 0;
            }
            int choice;
            cout << "Enter the type of operation to perform:\n"
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
                    return 0;
                }
                Relation *newRel= union_(relationmap[relName1], relationmap[relName2]);
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
                    return 0;
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
                    return 0;
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
                    return 0;
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
}