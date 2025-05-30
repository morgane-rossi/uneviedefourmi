#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <climits>

using namespace std;

int nbFourmis;
int nbSalles = 2 ;

/*
le code va travailler sur une seule fourmilière
dans un fichier "entree.txt"
*/

vector<string> readFile(){

    ifstream entree("entree.txt");
    vector<string> anthill ;

    if(!entree)
    {
        cerr << "Erreur lors du chargement du fichier" << endl ;
        return anthill;
    }
    string instruction ;
    while(getline(entree, instruction))
    {
        anthill.push_back(instruction);
    }
    return anthill ;
}

vector<string> parseInstructions(){

    vector<string> instructions = readFile();
    vector <string> graphes ;
;

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

    regex tiret(".* - .*");
    regex regex_single("^S\\d+$");
    regex regex_range("");

    // partie pour trouver nombre de fourmilières
    for (unsigned i = 1 ; i < instructions.size() ; i++)
    {
        ligne = instructions.at(i);
        // récupérer RE qui correspond ou non à la présence du caractère dans la ligne
        if (ligne.find('-') != string::npos)
        {
            graphes.push_back(ligne);
        }
        else
        {
            nbSalles++;
        }
    }
    return graphes ;
}

void DFS(int src, int dest, const vector<vector<int>> &graph, vector<int> &path, vector<vector<int>> &allPaths){
                                    
    // Add the current vertex to the path
    path.push_back(src);

    // Store the path when destination is reached
    if (src == dest){
        allPaths.push_back(path);
    }
    else{
        for (int adj_node:graph[src]){
            DFS(adj_node, dest, graph, path, allPaths);
        }
    }

    // remove the current vertex from the path
    path.pop_back();
}

vector<vector<int>> findPaths(vector<vector<int>> &graph, int src, int dest){

    vector<vector<int>> allPaths;
    vector<int> path;

    DFS(src, dest, graph, path, allPaths);

    return allPaths;
}

vector<vector<int>> buildGraph()
{
    vector<string> schema = parseInstructions();
    vector<vector<int>> anthill(nbSalles);
    int tailleInstructions = schema.size();
    /*
    le schema de la fourmilière est un tableau
    */
    for (int i = 0 ; i < tailleInstructions ; i++)
    {
        string ligne = schema.at(i);
        string v = "v";
        string d = "d";
        string zero = "0";
        string s = "S";
        string vide = "";
        string laste = to_string(nbSalles - 1) ;
        regex vto0(v);
        regex dtolast(d);
        regex sToVoid(s);
        ligne = regex_replace(ligne, vto0, zero);
        ligne = regex_replace(ligne, dtolast, laste);
        ligne = regex_replace(ligne, sToVoid, vide);

        int gauche, droite ;
        size_t dash_pos = ligne.find("-");
        string gauche_str = ligne.substr(0, dash_pos);
        string droite_str = ligne.substr(dash_pos+1);
        gauche = stoi(gauche_str);
        droite = stoi(droite_str);
        if (gauche <= droite)
        {
        anthill[gauche].push_back(droite);
        }
        else{
            anthill[droite].push_back(gauche);
        }
    }

    return anthill ;
}

void displayGraph(vector<vector<int>> graphe)
{
    for (const auto &path : graphe){
        for (int vtx : path){
            cout << vtx << " ";
        }
        cout << endl;
    }
}

void selectShortestGraphs(vector<vector<int>> graphe)
{
    // Étape 1 : Trouver la taille minimale
    size_t min_size = min_element(
        graphe.begin(), graphe.end(),
        [](const vector<int>& a, const vector<int>& b) {
            return a.size() < b.size();
        }
    )->size();

    // Étape 2 : Récupérer tous les vecteurs ayant cette taille
    vector<vector<int>> result;
    for (const auto& vec : graphe) {
        if (vec.size() == min_size) {
            result.push_back(vec);
        }
    }

    // Affichage du résultat
    cout << "Vecteurs de taille minimale (" << min_size << ") :\n";
    for (const auto& vec : result) {
        cout << "[ ";
        for (int val : vec) {
            cout << val << " ";
        }
        cout << "]\n";
    }
}

int main()
{
    vector<vector<int>> anthill = buildGraph();

    int last = anthill.size() - 1 ;
    vector<vector<int>> paths = findPaths(anthill, 0, last);

    displayGraph(paths);
    selectShortestGraphs(paths);

    return 0 ;
}