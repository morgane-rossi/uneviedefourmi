#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <regex>

using namespace std;

int nbFourmis;
int nbSalles = 2 ;

/*
le code va travailler sur une seule fourmilière
dans un fichier "entree.txt"
*/

vector<string> lireFichier(){

    ifstream entree("entree.txt");
    vector<string> fourmiliere ;

    if(!entree)
    {
        cerr << "Erreur lors du chargement du fichier" << endl ;
        return fourmiliere;
    }
    string instruction ;
    while(getline(entree, instruction))
    {
        fourmiliere.push_back(instruction);
    }
    return fourmiliere ;
}


vector<string> convertirInstructions(){

    vector<string> instructions = lireFichier();

    // partie pour trouver le nombre de fourmis
    string ligne = instructions.at(0);
//    regex b = ("\d"); 
    // Trouve la position du caractère '='
    int pos = ligne.find('=');

    // vérifie si "=" a été trouvé
    if (pos != string::npos){

        // extraire la sous-chaîne après "=" et la convertir en entier
        string numberStr = ligne.substr(pos+1);
        nbFourmis = stoi(numberStr);
    }
    cout << "nombre de fourmis : " << nbFourmis <<endl ;

    regex tiret(".* - .*");
    regex regex_single("^S\d+$");
    regex regex_range("");

    // partie pour trouver nombre de fourmilières
    for (unsigned i = 1 ; i < instructions.size() ; i++)
    {
        ligne = instructions.at(i);
        // récupérer RE qui correspond ou non à la présence du caractère dans la ligne
        if (ligne.find('-') != string::npos)
        {
            cout <<"";
        }
        else
        {
            nbSalles++;
        }

    }
    cout << "nombre de salles : " << nbSalles << endl;

    return instructions ;
}


int main()

{

    convertirInstructions();

    return 0 ;
}