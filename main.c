// Burlacu Andrei 312 CB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	struct node *children[27];
} Node, *Tree, *Queue;

Tree create_node() {
	Tree arbore = (Tree) malloc(sizeof(Node));			// aloca memorie pentru un element de tip Tree
	if(arbore != NULL) {
		int i;
		for(i = 0; i < 27; i++) {
			arbore->children[i] = NULL;
		}
	}
	return arbore;
}

void insert_word(Node *radacina, const char *cuvant, int k, FILE *out) {
	Node *aux = radacina;
	int index, nr = 0;
	int i;
	for(i = 0; i < strlen(cuvant); i++) {			// pentru fiecare litera din cuvant creez un nod nou daca nu exista
		if(cuvant[i] == '$')							// un nod copil cu acelasi index ca si parintele si in caz contrar
			index = 0;									// parcurg arborele mai departe in adancime
		else index = cuvant[i] - 'a' + 1;
		if(aux->children[index] == NULL) {
			nr++;										// numar cate noduri noi au fost create
			aux->children[index] = create_node();
		}
		aux = aux->children[index];
	}
	if(k == 3) {
		if(nr == 0)
			fprintf(out, "1\n");
		else fprintf(out, "0\n");
	}
}

void printSuffixTree(Node * root, FILE *out, int k){
	// parcurg arborele in latime (BFS)
	int x = 0;
	if (root == NULL)
		return;
	Node *queue[1000];
	int front = 0, rear = 0;
	queue[rear++] = root;			// adaug radacina in coada
	while (front != rear) {
		int level = rear - front;	// numarul de noduri de la nivelul curent

		int i;
		for(i = 0; i < level; i++) {
			Node *aux = queue[front++];		// extrag un nod din coada
			int j;
			for(j = 0; j < 27; j++) {
				if(aux->children[j] != NULL) {
					if(k == 1) {
						if(j == 0) fprintf(out, "$ ");		// afisez sufixele
						else fprintf(out, "%c ", 'a' + j - 1);
					}
					else if(k == 2) {
						if(j == 0){
							x++;			// numar frunzele din arbore
						}
					}
					queue[rear++] = aux->children[j];
				}
			}
		}
		if(rear != front && k == 1)
			fprintf(out, "\n");				// rand nou
	}
	if(k == 2) {
		fprintf(out, "%d\n", x);
	}
}

void numar_fii(Node *radacina, int *max_fii) {			// calclueza numarul maxim de fii ai unui nod
	if(radacina == NULL)
		return ;
	int nr_fii = 0;					// numarul de fii ai nodului curent
	int i;
	for(i = 0; i < 27; i++) {
		if(radacina->children[i] != NULL) {
			nr_fii++;
		}
	}
	if(nr_fii > *max_fii)			// updatez maximul
		*max_fii = nr_fii;
	for(i = 0; i < 27; i++)		// parcurg in adancime toti copii nodului curent
		numar_fii(radacina->children[i], max_fii);
}

void sufixe_k(Node *radacina, int k, int *nr, int len) {			//  numarul de sufixe de lungime k
	if(radacina == NULL)
		return ;
	int i;
	for(i = 0; i < 27; i++) {
		if(radacina->children[i] != NULL) {
			if(i == 0 && k == len)							// daca $ se afla pe nivelul k inseamna ca sufixul are lungime k
				(*nr)++;
			else
				sufixe_k(radacina->children[i], k, nr, len + 1);		// altfel parcurg mai departe in adancime
		}
	}
}

void free_tree(Node *radacina) {
	if(radacina == NULL)
		return;
	int i;
	for(i = 0; i < 27; i++)					// parcurg arborele in adancime si il dezaloc
		free_tree(radacina->children[i]);
	free(radacina);
}

int main(int argc, char *argv[]) {
	// citesc argumetele, trand cazul pentru -c2 cand apare un argument in plus
	char *option = argv[1];
	char *input_file, *output_file;
	int parametru;
	if(strcmp(option, "-c2") != 0) {
		input_file = argv[2];
		output_file = argv[3];
	}
	else {
		parametru = atoi (argv[2]);
		input_file = argv[3];
		output_file = argv[4];
	}

	FILE *in = fopen(input_file, "r");
	FILE *out = fopen(output_file, "w");

	Node *radacina = create_node(); // creez radacina arborelui
	int m;
	if(strcmp(option, "-c1") == 0 || strcmp(option, "-c2") == 0 || strcmp(option, "-c3") == 0) {
		int n;
		fscanf(in, "%d", &n);		// citesc numarul de cuvinte din care se formeaza arborele
		if(strcmp(option, "-c3") == 0) {
			fscanf(in, "%d", &m);	// numarul de sufixe pentru -c3
		}

		int i;
		for (i = 0; i < n; i++) {
			char cuvant[100];
			fscanf(in, "%s", cuvant);
			char sufix[100] = "";
			int i;
			for (i = strlen(cuvant); i >= 0; i--) {                // parcurg fiecare cuvant si formez un sir din ultimele caractere
				char cat[2] = "";
				cat[0] = cuvant[i];
				strcat(sufix, cat);
				char word[100];
				strcpy(word, sufix);
				int j;
				for (j = 0; j < strlen(word) / 2; j++) {            // inversez sirul si pun $, formand sufixul
					char tmp = word[j];
					word[j] = word[strlen(word) - j - 1];
					word[strlen(word) - j - 1] = tmp;
				}
				strcat(word, "$");
				insert_word(radacina, word, 0, out);				// inserez sufixul respectiv in arbore
			}
		}
	}
	if(strcmp(option, "-c1") == 0)						// construiesc arborele pt -c1
		printSuffixTree(radacina, out, 1);
	else if(strcmp(option, "-c2") == 0) {				// printez cele 3 statistici pentru -c3
		printSuffixTree(radacina, out, 2);
		int a = 0;
		sufixe_k(radacina, parametru, &a, 0);
		fprintf(out, "%d\n", a);
		int x = 0;
		numar_fii(radacina, &x);
		fprintf(out, "%d\n", x);
	}
	else if(strcmp(option, "-c3") == 0)  {			// inserez in arbore fiecare sufix si verific daca se modifica ceva la arobre
		char word[100];
		int i;
		for(i = 0; i < m; i++) {
			fscanf(in, "%s", word);
			strcat(word, "$");
			insert_word(radacina, word, 3, out);
		}
	}
	fclose(in);
	fclose(out);
	free_tree(radacina);	// eliberez memoria
	return 0;
}
