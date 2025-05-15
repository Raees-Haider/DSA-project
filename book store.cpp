#include <iostream>
#include <fstream>
#include <string>

int abc = 1; // product id
int bi = 0; // array index
int sum = 0; // total bill
int buy[100] = {0}; // what is bought
int how[100] = {0}; // how much
using namespace std;

class node {
public:
    int pro_id;
    string pro_name;
    int cat_id;
    string cat_name;
    int pro_qun;
    int pro_pri;
    node* next;
};

class link {
private:
    node *head, *tail;

    void save_to_file() {
        ofstream file("products.txt");
        node *current = head;
        while (current != NULL) {
            file << current->pro_id << " " << current->cat_id << " " << current->pro_qun << " " << current->pro_pri << " "
                 << current->pro_name << "|" << current->cat_name << endl;
            current = current->next;
        }
        file.close();
    }

public:
    link() {
        head = NULL;
        tail = NULL;
        load_from_file();
    }

    ~link() {
        save_to_file();
    }

    void load_from_file() {
        ifstream file("products.txt");
        if (!file.is_open()) return;

        node *temp;
        while (!file.eof()) {
            temp = new node;
            file >> temp->pro_id >> temp->cat_id >> temp->pro_qun >> temp->pro_pri;
            file.ignore();
            getline(file, temp->pro_name, '|');
            getline(file, temp->cat_name);
            if (file.fail()) {
                delete temp;
                break;
            }
            temp->next = head;
            head = temp;
        }
        file.close();

        // Update the global product id counter to avoid conflicts
        if (head != NULL) {
            abc = head->pro_id + 1;
        }
    }

    void add_new_item(int ci, string pn, string cn, int pq, int pp) {
        node *temp = new node;
        temp->pro_id = abc++;
        temp->cat_id = ci;
        temp->pro_name = pn;
        temp->cat_name = cn;
        temp->pro_qun = pq;
        temp->pro_pri = pp;
        temp->next = head;
        head = temp;

        save_to_file();
    }

    void delete_position(int pro_id) {
        node *current = head;
        node *previous = NULL;
        while (current != NULL) {
            if (current->pro_id == pro_id) {
                if (previous == NULL) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                save_to_file();
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    void sub_howmany(int pro_id, int how) {
        node *current = head;
        while (current != NULL) {
            if (current->pro_id == pro_id) {
                current->pro_qun -= how;
                save_to_file();
                return;
            }
            current = current->next;
        }
    }

    void display() {
        node *tmp = head;
        cout << "Your Products are " << endl << endl;
        cout << "Id        Price        Quantity         Category             Name" << endl;
        cout << "=======================================================================" << endl;

        while (tmp != NULL) {
            cout << tmp->pro_id << "          " << tmp->pro_pri << "            " << tmp->pro_qun << "            " << tmp->cat_name << "           " << tmp->pro_name << endl;
            tmp = tmp->next;
        }
    }

    void display_customer(int a) {
        node *tmp = head;
        cout << "Your Products are " << endl << endl;
        cout << "Id           Price              Name" << endl;
        cout << "==========================================" << endl;
        while (tmp != NULL) {
            if (tmp->cat_id == a) {
                cout << tmp->pro_id << "             " << tmp->pro_pri << "              " << tmp->pro_name << endl;
            }
            tmp = tmp->next;
        }
    }

    int display_bill(int a, int b) {
        node *tmp = head;
        while (tmp != NULL) {
            if (tmp->pro_id == a) {
                cout << tmp->pro_id << "            " << tmp->pro_pri << "             " << b << "              " << tmp->pro_name << endl;
                return tmp->pro_pri;
            }
            tmp = tmp->next;
        }
        return 0;
    }

    int check_qun(int qun, int pid) {
        node *tmp = head;
        while (tmp != NULL) {
            if (tmp->pro_id == pid) {
                if (tmp->pro_qun >= qun) return 0;
            }
            tmp = tmp->next;
        }
        return 1;
    }
};

link obj;

int main() {
    while (true) {
        system("CLS");
        cout << "Welcome to Book Mart" << endl;
        cout << "Press corresponding number " << endl;
        cout << "1. Admin " << endl;
        cout << "2. Customer " << endl;
        cout << "0. Exit " << endl;
        int cho;
        cin >> cho;
        if (cho == 1) {
            while (true) {
                system("CLS");
                cout << "Press corresponding number " << endl;
                cout << "1. Add product" << endl;
                cout << "2. View all product" << endl;
                cout << "3. Delete any product" << endl;
                cout << "0. Back " << endl;
                cout << "Your choice : ";
                int choo;
                cin >> choo;
                if (choo == 1) {
                    string pro_name;
                    int cat_id;
                    string cat_name;
                    int pro_qun;
                    int pro_pri;
                    cout << "Press corresponding number for product Category: " << endl;
                    cout << "1. Books" << endl;
                    cout << "2. Pen " << endl;
                    cout << "3. Color" << endl;
                    cout << "4. Marker " << endl;
                    cout << "5. Register" << endl;
                    cin >> cat_id;
                    switch (cat_id) {
                        case 1: cat_name = "Books"; break;
                        case 2: cat_name = "Pen"; break;
                        case 3: cat_name = "Color"; break;
                        case 4: cat_name = "Marker"; break;
                        case 5: cat_name = "Register"; break;
                        default:
                            cout << "Invalid entry, try again!" << endl;
                            system("pause");
                            continue;
                    }
                    cout << "Enter product Quantity : ";
                    cin >> pro_qun;
                    cout << "Enter product Price : ";
                    cin >> pro_pri;
                    cout << "Enter product Name : ";
                    cin.ignore();
                    getline(cin, pro_name);
                    obj.add_new_item(cat_id, pro_name, cat_name, pro_qun, pro_pri);
                } else if (choo == 2) {
                    obj.display();
                    system("pause");
                } else if (choo == 3) {
                    cout << "Enter Product ID : ";
                    int a;
                    cin >> a;
                    obj.delete_position(a);
                    system("pause");
                } else if (choo == 0) {
                    break;
                } else {
                    cout << "Wrong entry!" << endl;
                    system("pause");
                }
            }
        } else if (cho == 2) {
            while (true) {
                system("CLS");
                cout << "Press corresponding number " << endl;
                cout << "1. View Product" << endl;
                cout << "2. Purchase" << endl;
                cout << "3. Bill " << endl;
                cout << "0. Back " << endl;
                cout << "Your choice : ";
                int choo;
                cin >> choo;
                if (choo == 1) {
                    cout << "Press corresponding number for product Category : " << endl;
                    cout << "1. Books" << endl;
                    cout << "2. Pen " << endl;
                    cout << "3. Color" << endl;
                    cout << "4. Marker " << endl;
                    cout << "5. Register" << endl;
                    int a;
                    cin >> a;
                    obj.display_customer(a);
                    system("pause");
                } else if (choo == 2) {
                    cout << "Press corresponding number for product Category : " << endl;
                    cout << "1. Books" << endl;
                    cout << "2. Pen " << endl;
                    cout << "3. Color" << endl;
                    cout << "4. Marker " << endl;
                    cout << "5. Register" << endl;
                    cout << "0. Back " << endl;
                    int a;
                    cin >> a;
                    if (a == 0) {
                        break;
                    }
                    obj.display_customer(a);
                    cout << "Press corresponding number to buy " << endl;
                    int pid;
                    cin >> pid;
                    cout << "How much you want : ";
                    int xc;
                    cin >> xc;
                    int x = obj.check_qun(xc, pid);
                    if (x) {
                        cout << "We don't have that much Quantity. " << endl;
                        system("pause");
                    } else {
                        buy[bi] = pid;
                        how[bi] = xc;
                        bi++;
                        obj.sub_howmany(pid, xc);
                        system("pause");
                    }
                } else if (choo == 3) {
                    cout << "Your Products are " << endl << endl;
                    cout << "Id          Price          Quantity             Name" << endl;
                    cout << "============================================================" << endl;
                    int t;
                    sum = 0;
                    for (int i = 0; i < bi; i++) {
                        t = obj.display_bill(buy[i], how[i]);
                        sum += (t * how[i]);
                    }
                    cout << "============================================================" << endl;
                    cout << "Total bill is :  " << sum << endl << endl;
                    system("pause");
                } else if (choo == 0) {
                    break;
                } else {
                    cout << "Wrong entry!" << endl;
                    system("pause");
                }
            }
        } else if (cho == 0) {
            system("CLS");
            cout << "Goodbye" << endl;
            break;
        } else {
            cout << "Wrong entry" << endl;
            system("pause");
        }
    }
    return 0;
}

