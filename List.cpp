#include "List.h"

List::List()
{
/* 
    Konstruktor für eine leere Liste 
*/
    head_tail       = new Node;
    list_size       = 0;
    temp            = false;
    head_tail->next = head_tail;
    head_tail->prev = head_tail;
}

List::List(const List& _List)
{
/*  
    Konstruktor mit Übergabe einer Liste, die dann kopiert wird. 
    in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    sollen.
*/
    list_form       = _List.list_form;
    head_tail       = new Node;
    list_size       = 0;
    temp            = _List.temp;
    head_tail->next = head_tail;        
    head_tail->prev = head_tail;
    Node* tmp_node;
    tmp_node = _List.head_tail->next;
    while (tmp_node != _List.head_tail)
    {
        head_tail->prev =
            new Node(tmp_node->value, head_tail->prev->next, head_tail->prev);
        head_tail->prev->prev->next = head_tail->prev;
        list_size++;
        tmp_node = tmp_node->next;
    }
/*  
    Ist die übergebene Liste eine temporäre Liste? -> aus Operator +
*/
    if (_List.temp)
        delete &_List; 
}

List::~List()
{
    /*
    TODO:
    Dekonstruktor
    Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.
    */

    /*
     Wir iterieren die liste dabei biegen wir die Pointer um und 
     löschen den vorgänger ab dem 1. Element der liste
    */
    while(head_tail->next != head_tail)
    {    
        head_tail->next->prev = nullptr;
        head_tail->next->next = head_tail->next;
        delete head_tail->next->prev;
        head_tail->next->prev = head_tail;
    }

    // Somit ist die Komplette liste inkl. head_tail gelöscht. Allokierter Speicher wieder freigegeben.
    delete head_tail;


}

void List::insertFront(int value)
{

    /*
    TODO: Einfuegen eines neuen Knotens am Anfang der Liste
          einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
    */

    // (1) Initialisieren des neuen Knotens.
    Node *new_Node = new Node(value);
    new_Node->next = nullptr;
    new_Node->prev = nullptr;

    // (2) Knoten in die Liste einbinden
    new_Node->next = head_tail;
    new_Node->prev = head_tail;

    head_tail->next = new_Node;
    head_tail->prev = new_Node;
}

void List::insertFront(List& _List)
{
    
    /*
    TODO:

    Einfuegen der Liste _List am Anfang an einer vorhandenen Liste
	Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
	Die einzufuegende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden. 
    */

    /*
    gleiches Objekt -> keine Aktion
    */ 
	if (head_tail == _List.head_tail) return;	

    /*
	Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
	Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
	Die Liste _List ist danach leer, aber vorhanden.
    */

     // Aktualisierung der Listen größe;
     this->list_size += _List.list_size; 

     //Verkettung der zwei Listen
    _List.head_tail->prev->next = this->head_tail->next;
    this->head_tail->next->prev = _List.head_tail->prev;
    _List.head_tail->next = this->head_tail->next;
    this->head_tail->next->prev = head_tail;

    // Leere Liste die auf sich selber zeigt.
    _List.head_tail->next = _List.head_tail;
    _List.head_tail->prev = _List.head_tail;

}

void List::insertBack(int value)
{
    
    /*
    TODO:
	Einfuegen eines neuen Knotens am Ende der Liste
    Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
    */

    // Initialisierung des Neuen Knoten
    Node* new_Node = new Node(value);
    new_Node->next = nullptr;
    new_Node->prev = nullptr;

    // Einfügen des neues Knoten in einer Vorhandenen Liste am Ende.
    new_Node->next = head_tail;
    new_Node->prev = head_tail->prev;

    head_tail->prev->next = new_Node;
    head_tail->prev = new_Node;

    list_size++;

}

void List::insertBack(List& _List)
{
    
    /*
    TODO;
    Einfuegen der Liste _List am Ende einer vorhandenen Liste
	Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
	Die einzufuegende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden. 
    */

    /*
    gleiches Objekt -> keine Aktion
    */
	if (head_tail == _List.head_tail) return;

    /*
	Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
	Diese Knoten (koplette Kette) werden an den Ende der Liste (this) übertragen ohne sie zu kopieren!
	Die Liste _List ist danach leer, aber vorhanden.
    */

   _List.head_tail->next->prev = head_tail->prev;
    head_tail->prev->next = _List.head_tail->next;

    head_tail->prev = _List.head_tail->prev->next;
    _List.head_tail->prev->next = head_tail;


}

bool List::getFront(int& value)
{
    
    /*  
    TODO:
    entnehmen des Knotens am Anfang der Liste
	der Wert wird als Parameter zurueckgegeben
	der Knoten wird entnommen
	im Fehlerfall wird false zurückgegeben
    */

    /*
    gleiches Objekt -> keine Aktion
    */
	if (!list_size) return false;	

    /*
	Der Wert des vorderen Knotens wird rückgegeben und der Knoten gelöscht.
	Die Methode del(value) darf nicht zum löschen benutzt werden.
    */

    if(head_tail->next->value == value)
    {
        return true;    
    }
    else
    {
         return false;
    }

}

bool List::getBack(int& value)
{ 
    //ToDo
/*  
    entnehmen des Knotens am Ende der Liste
	der Wert wird als Parameter zurueckgegeben
	der Knoten wird entnommen
	im Fehlerfall wird false zurückgegeben
*/

/*
    gleiches Objekt -> keine Aktion
*/
	if (!list_size) return false;

/*
	Der Wert des letzten Knotens wird rückgegeben und der Knoten gelöscht.
	Die Methode del(value) darf nicht zum löschen benutzt werden.
*/

}

bool List::del(int value)
{
    
    
    // TODO:   Loeschen eines gegebenen Knotens im Fehlerfall wird false zurückgegeben

    /*
        gleiches Objekt -> keine Aktion
    */
	if (!list_size) return false;

    Node *tmp = head_tail->next;

    bool found = false;

    while(tmp->next != head_tail)
    {
        if(tmp->value == value)
        {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;

            delete tmp;
            list_size--;
            found = true;
        }
        tmp = tmp->next;
    }
    if(found == false)return false; // Keine übereinstimmung gefunden.
}

bool List::search(int value)
{
    
   // TODO : Suchen eines Knoten nicht gefunden -> Rueckgabe: false

    /*
        leere Liste -> keine Aktion
    */
    if (!list_size) return false; 

    bool not_exist = true;
    while(head_tail->next != head_tail){
        if(head_tail->next->value == value)
        {
                not_exist = false;
                return true;
        }
      head_tail->next = head_tail->next->next;
    }
    if(not_exist == true) return false;

}

bool List::swap(int value1, int value2)
{
    
    /* 
    TODO: Vertauschen von zwei Knoten
        - Dabei werden die Zeiger der Knoten und deren Nachbarn veraendert
            und im Fehlerfall wird false zurueckgegeben
    */

    /*
        Wenn Liste Leer oder weniger als 2 Knoten besitzt -> Keine Aktion
    */
	if (list_size < 2) return false; 

    /*
        Vertauschen von zwei Knoten mit dem Wert value1 und dem Wert value2.
        Es duerfen nicht nur einfach die Werte in den Knoten getauscht werden!
        Die Knoten sind in der Kette umzuhaengen.
    */
    Node *tmp = head_tail->next;
    Node *tmp_value_1 = new Node;
    Node *tmp_value_2 = new Node;

    while(tmp->next != head_tail)
    {
        if(tmp->value == value1)
        {
            tmp_value_1 = tmp;
        }
        else if(tmp->value == value2){
            tmp_value_2 = tmp;
        }
        tmp = tmp->next;
    }

    // Tauschen der Knoten
    tmp_value_1->next = tmp_value_2 -> next;
    tmp_value_2->next->prev = tmp_value_1;

    tmp_value_2->next
   

	return true;
}

int List::size(void)
{
   
    /*  
        TODO:
        Rueckgabe der Anzahl der Knoten in der Liste mit O(1)
        d.h. die Liste darf NICHT traversiert werden um die Größe zu bestimmen.

        Anzahl der Knoten in der Liste zurückgeben.
        Hier richtiges Ergebnis zurückgeben
    */
   if(list_size > 0) return list_size;
	return 0;	
}

bool List::test(void)
{
    // Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und
    // zurück Es werden dabei die Anzahl der Knoten gezahlt. Stimmt die Anzahl
    // der Knoten überein liefert die Methode true
    Node* tmp    = head_tail->next;
    int   i_next = 0, i_prev = 0;
    while (tmp != head_tail)
    {
        tmp = tmp->next;
        if (i_next > list_size)
            return false;
        i_next++;
    }
    if (i_next != list_size)
        return false;
    tmp = head_tail->prev;
    while (tmp != head_tail)
    {
        tmp = tmp->prev;
        if (i_prev > list_size)
            return false;
        i_prev++;
    }
    return i_prev == i_next;
}

List& List::operator=(const List& _List)
{
    // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    // sollen. Kopiert wird in das Objekt "this"
    if (this == &_List)
        return *this; //  !! keine Aktion notwendig
    list_form = _List.list_form;
    Node* tmp_node;
    if (list_size)
    {
        Node* tmp_del;
        tmp_node = head_tail->next;
        while (tmp_node !=
               head_tail) // Alle eventuell vorhandenen Knoten in this löschen
        {
            tmp_del  = tmp_node;
            tmp_node = tmp_node->next;
            delete tmp_del;
        }
        list_size       = 0;
        head_tail->next = head_tail;
        head_tail->prev = head_tail;
    }
    tmp_node = _List.head_tail->next; // Die Listen-Knotenwerte werden kopiert
    while (tmp_node != _List.head_tail)
    {
        insertBack(tmp_node->value);
        tmp_node = tmp_node->next;
    }
    if (_List.temp)
        delete &_List; // ist die übergebene Liste eine temporäre Liste? -> aus
                       // Operator +
    return *this;
}

List& List::operator+(const List& List_Append)
{
    // Die Methode +
    // Es werden zwei Listen aneinander gehangen.
    // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
    // Ergebnisliste.
    Node* tmp_node;
    List* tmp;
    if (temp)
    { // this ist eine temporäre Liste und kann verändert werden
        tmp = this;
    }
    else
    {
        tmp =
            new List(*this); // this ist keine temporäre Liste -> Kopie erzeugen
        tmp->temp = true;    // Merker setzten, dass es sich um eine temporäre
                             // Liste handelt
    }
    if (List_Append.list_size)
    { // anhängen der übergebenen Liste an tmp
        tmp_node = List_Append.head_tail->next;
        while (tmp_node != List_Append.head_tail)
        {
            tmp->insertBack(tmp_node->value);
            tmp_node = tmp_node->next;
        }
    }
    if (List_Append.temp)
        delete &List_Append; // wurde eine temporäre Liste übergeben, dann wird
                             // diese gelöscht
    return *tmp;
}

void List::format(const std::string& start,
                  const std::string& zwischen,
                  const std::string& ende)
{
    // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
    // das Format wird für den überladenen Operator << verwendet
    list_form.start    = start;
    list_form.zwischen = zwischen;
    list_form.ende     = ende;
}

std::ostream& operator<<(std::ostream& stream, List const& Liste)
{
    // Ausgabe der Liste mit cout
    stream << Liste.list_form.start;
    for (Node* tmp = Liste.head_tail->next; tmp != Liste.head_tail;
         tmp       = tmp->next)
        stream << tmp->value
               << (tmp->next == Liste.head_tail ? Liste.list_form.ende :
                                                  Liste.list_form.zwischen);
    if (Liste.temp)
        delete &Liste; // wurde eine temporäre Liste übergeben, dann wird diese
                       // gelöscht
    return stream;
}
