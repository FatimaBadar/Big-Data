#include<iostream>
using namespace std;
#include<fstream>
#include<stack>
#include<string>
//#include<stdio.h>
#include<conio.h>

int count=1;

class tree{
	public:

		string snum, userId, movieId, movieName, rating, genre, date, duration, imdbTitle, director, overview;
		tree *left, *right;
		int height;
		int bf;
				
		tree(){		}
		
		tree(string s, string u, string mi, string mN, string r, string g, string da, string dur, string imT, string dir, string o){
			snum = s;
			userId = u;
			movieId = mi;
			movieName = mN;
			rating = r;
			genre = g;
			date = da;
			duration = dur;
			imdbTitle = imT;
			director = dir;
			overview = o;
			left = NULL;
			right = NULL;
		}
};

int message(){
	
	int i, j;
	for(i=1;i<=3;i++)
	{
		for(j=1; j<=120; j++)
		{
		    if(i==2 && j==2)
		    {
		        cout << "\t\t\t\t\t\t M O V I E S . C O M ";
		        continue;
		    }
		    
			else if(i==2 && j>=2 || i == 2 && j<=2)
		    cout << " ";
		    
			else
		    cout << "*";
	
		}
		cout << "\n";
	}
}

int m(string s){
	
	int i, j;
	for(i=1;i<=3;i++)
	{
		for(j=1; j<=120; j++)
		{
			 if(i==2 && j==2)
		    {
			cout<<"\n\t\t\t\t\t" << s << " \t\t\t\t \n";
		        continue;
		    }
		    
			else if(i==2 && j>=2 || i == 2 && j<=2)
		    cout << " ";
		    
			else
		    cout << "*";
		}
		cout <<"\n";
	}
}

int getHeight(tree *root){
	int lefth=0, righth=0; 
	if(root == NULL){
		return -1;
	}
	else{
		lefth = getHeight(root->left);
		righth = getHeight(root->right);
	}
	
	if(lefth > righth){
		return (lefth + 1);
	}
	else
	return (righth + 1);
}

int balanceFactor(tree* node){
	if(node==NULL){
		return -1;
	}
	return getHeight(node->left) - getHeight(node->right);
}

tree* rightR(tree *root){
	tree *temp = root;
	tree *x = temp->left;
	tree *y = x->right;
	
	x->right = temp;
	temp->left = y;
	
	temp->height = getHeight(temp);
	x->height = getHeight(x);

    return x;
}

tree* leftR(tree *root){	
	tree *temp = root;
	tree *x = temp->right;
   // tree* rl =  r->left;
    tree *y = x->left;
    x->left = root;
    root->right = y;

	temp->height = getHeight(temp);
	x->height = getHeight(x);
	
    return x;
}

tree* insert(tree* root, string s, string u, string mi, string mN, string r, string g, string da, string dur, string imT, string dir, string o){
//	cout << "\nInserting";
	if(root==NULL){
		tree *n = new tree(s,  u,  mi,  mN,  r,  g,  da,  dur,  imT,  dir,  o);
		return n;
	}
	
	if(mi < root->movieId){
		root->left = insert(root->left, s,  u,  mi,  mN,  r,  g,  da,  dur,  imT,  dir,  o); //jitne parameters h wou saare ayenge 	
	}
	
	else if(mi > root->movieId){
	    root->right = insert(root->right, s,  u,  mi,  mN,  r,  g,  da,  dur,  imT,  dir,  o);
    }
    else
    return root;
    
    root->height = getHeight(root);
//	root->bf
//cout << "\nroot->height " << root->height;
	int b = balanceFactor(root);
//	cout << "\nbalance: " << b;

    if(b > 1 && mi < root->left->movieId){
    	return rightR(root);
	}
	if(b <-1 && mi > root->right->movieId){ 
		return leftR(root);
	}
	if(b > 1 && mi > root->left->movieId){ 
		root->left = leftR(root->left);
		return rightR(root);
	}
	if(b <-1 && mi < root->right->movieId){ 
		root->right = rightR(root->right);
		return leftR(root);
	}
		
	return root;	
}

void inorder(tree *root){
	if(root==NULL){
//		cout << "root is null";
		return;
	}
	inorder(root->left);

	cout << "Serial number: " << root->snum <<endl;
	cout << "User Id: " << root->userId << endl;
	cout << "Movie Id: " << root->movieId << endl;
	cout << "Movie Name: " << root->movieName << endl;
	cout << "Rating: " << root->rating << endl;
	cout << "Genre: " << root->genre << endl;
	cout << "Date: " << root->date << " " << endl;
	cout << "Duration: " << root->duration << " " << endl;
	cout << "Imdb Title: " << root->imdbTitle << endl;
	cout << "Director: " << root->director << endl;
	cout << "Overview: " << root->overview << endl << endl;

	inorder(root->right);
}

tree* inordersucc(tree* root){
	tree* temp=root;
	
	while(temp && temp->left!=NULL){
	    temp = temp->left;
	}
	return temp;
}

tree* deleteByMovieID(tree* root, string mi){
//    cout << "Deleting: ";
	if(mi < root->movieId){
        root->left = deleteByMovieID(root->left, mi);
    }
   
    else if(mi > root->movieId){
        root->right = deleteByMovieID(root->right, mi);
    }
    
    else if(root->left == NULL){
        tree* temp = root->right;
		delete root;
		return temp;
    }
    
    else if(root->right == NULL){
	    tree* temp = root->left;
//        cout << "\n\n\n\t\t\t\t\t\t" << root->movieId << " deleted";
	    delete root;
		return temp;
    }
    
    else{
        tree* temp= inordersucc(root->right);
		root->movieId = temp->movieId;
		root->right = deleteByMovieID(root->right, temp->movieId);
    }
    return root;
    root->height = getHeight(root);
	int balance= balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightR(root);
 
    if (balance > 1 & balanceFactor(root->left) < 0){
        root->left = leftR(root->left);
        return rightR(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftR(root);
 
    if (balance < -1 && balanceFactor(root->right) > 0){
        root->right = rightR(root->right);
        return leftR(root);
    }

    return root;
}

//tree* searchByUserID(tree *root, string u){
//	if(root==NULL){
//	    return NULL;
//	}
//	if(root->userId == u){
//	    return root;
//    }
//    if(u < root->userId){
//	    return searchByUserID(root->left, u);
//    }
//    return searchByUserID(root->right, u);
//}

tree* searchByMovieID(tree *root, string mi){
	if(root==NULL){
	    return NULL;
    }
    if(root->movieId == mi){
        return root;
    }
    if(mi < root->movieId){
        return searchByMovieID(root->left, mi);
    }
    return searchByMovieID(root->right, mi);
}

//tree* searchByMoviename(tree *root, string mN){
////	cout << "in found";
//	if(root==NULL){
////		cout << "not found";
//	    return NULL;
//    }
//	if(root->movieName == mN){
////		cout << "found";
////		cout << "\nroot: " << root->date;
//        return root;
//    }
//    if(mN < root->movieName){
//        return searchByMoviename(root->left, mN);
//    }
//    return searchByMoviename(root->right, mN);
//}

void display(tree* root){
	
//	cout << "\n\nDetails: \n\n";
	cout << "\n\nSerial number: " << root->snum <<endl;
	cout << "User Id: " << root->userId << endl;
	cout << "Movie Id: " << root->movieId << endl;
	cout << "Movie Name: " << root->movieName << endl;
	cout << "Rating: " << root->rating << endl;
	cout << "Genre: " << root->genre << endl;
	cout << "Date: " << root->date << " " << endl;
	cout << "Duration: " << root->duration << " " << endl;
	cout << "Imdb Title: " << root->imdbTitle << endl;
	cout << "Director: " << root->director << endl;
	cout << "Overview: " << root->overview << endl << endl;
}

int SearchByMovieName(tree* root, string mN){
	cout << "\n\t\t\t\t\tPress any key to continue.";	
	getch();
	cout<<endl;
	system("cls");
	    
	string st = "D E T A I L S  O F  T H I S  M O V I E";
	m(st);
	
	int v=0;
    stack<tree*> s;
    tree *temp = root;
 
//    cout << "\n\nDetails of the Movie " << mN << ": \n\n";
    while (temp != NULL || s.empty() == false){
        while (temp !=  NULL){
            s.push(temp);
            temp = temp->left;
        }
 
        temp = s.top();
        s.pop();
        
        if(temp->movieName == mN){
        	
        	display(temp);
        	v++;
		}
		temp = temp->right;
    }
	    cout << "\n\t\t\t\t\tPress any key to continue.";	
	    getch();
	    cout<<endl;
    	system("cls");
    return v;
}	

int SearchByUserID(tree* root, string u){

	system("cls");

//    string st = "USER " + u + "'S MOVIE NAMES: ";
	string st = "U S E R ' S  M O V I E  N A M E S";
	
	m(st);
	int v=0;
    stack<tree*> s;
    tree *temp = root;
 
// 	cout << "User " << u << "'s Movie Names: \n";
    cout << endl;    
	while (temp != NULL || s.empty() == false){
        while (temp !=  NULL){
            s.push(temp);
            temp = temp->left;
        }
 
        temp = s.top();
        s.pop();
        
        if(temp->userId == u){
        	v++;
        	cout << temp->movieName << endl;
//        	display(temp);
//            cout << temp->userId << " ";
		}
		temp = temp->right;
    }
   
    string d;
    cout << "\n\n\n\t\t\t\t\tEnter the Movie Name for details: ";
//    cin.ignore();
    fflush(stdin);
    getline(cin, d);

    SearchByMovieName(root, d);
    
    return v;
}
	
int SearchByRating(tree* root){

	system("cls");
	
	string st = "T O P  F I V E  R A T E D  M O V I E S";
	m(st);

	int v=0;
    stack<tree*> s;
    tree *temp = root;
    
//	cout << "\n\nTop 5 rated movies:  \n\n";
    
	while (temp != NULL || s.empty() == false){
        while (temp !=  NULL){
            s.push(temp);
            temp = temp->left;
        }
 
        temp = s.top();
        s.pop();
        
        if(temp->rating == "5" && count<=5){
        	cout << "\nName: " << temp->movieName << " && Rating: " << temp->rating;
//        	display(temp);
            v++;
        	count++;

		}
		temp = temp->right;
    }
    
	string d;
    cout << "\n\n\n\t\t\t\t\tEnter the Movie Name for details: ";
//    cin.ignore();
    fflush(stdin);
    getline(cin, d);
    
    SearchByMovieName(root, d);
    return v;
}

int SearchByGenreRating2(tree* root, string g){

	system("cls");
	
	string st = "T O P  F I V E  R A T E D  M O V I E S  O F  \n\t\t\t\t\t      T H E  E N T E R E D  G E N R E ";
	m(st);
    
	fflush(stdin);
	int v=0;	
    stack<tree*> s;
    tree *temp = root;
    
//    cout << "\n\nTop 5 rated movies of the genre " << g << ":  \n\n";
    while (temp != NULL || s.empty() == false){
        while (temp !=  NULL){
//        	if(temp->genre == g){
        		s.push(temp);
                temp = temp->left;
//			}          
        }
 
        temp = s.top();
        s.pop();
        int p = temp->genre.find(g);
        if( p!=-1 && temp->rating >= "5" && count<=5){
        	cout << "\nName: " << temp->movieName << " && Rating: " << temp->rating;
//        	display(temp);
        	count++;
        	v++;
		}
		temp = temp->right;
    }

    string d;
    cout << "\n\n\n\t\t\t\t\tEnter the Movie Name for details: ";
//    cin.ignore();
    fflush(stdin);
    getline(cin, d);
    SearchByMovieName(root, d);
    return v;
}

int SearchByGenre(tree* root, string str){

	system("cls");
	    
	string st = "M O V I E S  O F  E N T E R E D  G E N R E ";
	m(st);

	int v=0;
    stack<tree*> s;
    tree *temp = root;
  	
//    cout << "\n\nMovies of the genre " << str << ":  \n\n";
    cout << endl;
    while (temp != NULL || s.empty() == false){
        while (temp !=  NULL){
            s.push(temp);
            temp = temp->left;
        }
 
        temp = s.top();
        s.pop();
        ///
        int p = temp->genre.find(str);
		if(p !=-1){ //!= string::npos){
		v++;
	        	cout << temp->movieName << endl;
		
//			display(temp); 
		}	

		temp = temp->right;
    }
    
	string d;
    cout << "\n\n\n\t\t\t\t\tEnter the Movie Name for details: ";
//    cin.ignore();
    fflush(stdin);
    getline(cin, d);
    SearchByMovieName(root, d);
	    
    return v;
}

int main() {
	system("color 80");

	message();
	
	tree *root = NULL;
    tree *temp =NULL;

	ifstream in1("movies.csv");
	ifstream in2("overview.csv");
	
	if(!in1.is_open()){
				cout << "error file 1open!" << endl;
	}
	if(!in2.is_open() ){
		cout << "error file 2open!" << endl;
	}

	string snum, userId, movieId, movieName, rating, genre, date, duration, imdbTitle, director, overview;

    int i=0;	
	while(in1.good() || in2.good() ) {

		fflush(stdin);
		getline(in1, snum, ',');
		fflush(stdin);
		getline(in1, userId, ',');
		fflush(stdin);
		getline(in1, movieId, ',');
		fflush(stdin);
		getline(in1, movieName, ',');
		fflush(stdin);
		getline(in1, rating, ',');
		fflush(stdin);
		getline(in1, genre, ',');
		fflush(stdin);
		getline(in1, date, ',');
		fflush(stdin);
		getline(in1, duration, ',');
		fflush(stdin);
		getline(in1, imdbTitle, ',');
		fflush(stdin);
		getline(in1, director, '\n');
		fflush(stdin);
		getline(in2, overview, '\n');
		fflush(stdin);
		
	//}
//        cout << "Serial number: " << snum <<endl;
//		cout << "userId: " << userId << endl;
//		cout << "movieId: " << movieId << endl;
//		cout << "movieName: " << movieName << endl;
//		cout << "rating: " << rating << endl;
//		cout << "genre: " << genre << endl;
//		cout << "date: " << date << " " << endl;
//		cout << "duration: " << duration << " " << endl;
//		cout << "imdbTitle: " << imdbTitle << endl;
//		cout << "director: " << director << endl;
//		cout << "overview: " << overview << endl << endl;
     
//    if(i==0){
//        root = insert(root, snum, userId, movieId, movieName, rating, genre, date, duration, imdbTitle, director, overview);	
//	}
    if(i>=0 && i<=10000){
//    	cout << "\ninside if";
		root = insert(root, snum, userId, movieId, movieName, rating, genre, date, duration, imdbTitle, director, overview);
	}
//	else
//    root = 
//    insert(root, snum, userId, movieId, movieName, rating, genre, date, duration, imdbTitle, director, overview);	
	
	i++;
	}	
//	cout << "\n\n\n\nINORDER:\n";
//	inorder(root);	

	in1.close();
	in2.close();	
//	cout << "\n\nDFS: ";
	string u, mN, mi, g, g2;
	int choice, next, j=0;
    do
	{
//    	cout << "root: " <<root->movieName;

        cout << "\n\t\t\t\t\t\tWELCOME TO MOVIES.COM\n";
        cout << "\n\t\t\t\t\t\t1. SEARCH BY USER ID";
        cout << "\n\t\t\t\t\t\t2. SEARCH BY MOVIE ID";
        cout << "\n\t\t\t\t\t\t3. SEARCH BY MOVIE NAME";
        cout << "\n\t\t\t\t\t\t4. SEARCH BY GENRE";        
        cout << "\n\t\t\t\t\t\t5. TOP FIVE RATED MOVIES";        
        cout << "\n\t\t\t\t\t\t6. SEARCH HIGHEST RATED MOVIES BY GENRE";
        cout << "\n\t\t\t\t\t\t7. DELETE BY MOVIE ID";
        cout << "\n\t\t\t\t\t\t8. EXIT";
        cout << "\n\n\t\t\t\t\t\tEnter choice: ";
        cin >> choice;
        switch(choice){
        	case 1:
        		{
				cout << "\n\n\n\t\t\t\t\t\tEnter User ID: ";
//        		cin.ignore();
//        		getline(cin, u);
				cin >> u; 

				int l = SearchByUserID(root, u);
				if(l == 0){
					cout << "\n\n\n\t\t\t\t\t\tNot found";
				}
				}
				
                break;
                          
            case 2:{
        		cout << "\n\n\n\t\t\t\t\t\tEnter Movie ID: ";
        		cin >> mi;
//        		getline(cin, m);

				temp = searchByMovieID(root, mi);

                if( temp !=NULL){
   	               	system("cls");

                	string st = "M O V I E  N A M E S  W I T H  E N T E R E D  I D ";
	                m(st);
//					cout << "\n\nMovie with the ID " << m << ": \n\n";
					display(temp);				
				} 
				else{
					cout << "\n\n\n\t\t\t\t\t\tNot found\n";
				}
			}
				break;
            
            case 3:{
            	cout << "\n\n\n\t\t\t\t\t\tEnter Movie Name: ";
                cin.ignore();
				getline(cin, mN);	
				int k = SearchByMovieName(root, mN);
				
				if(k==0){
					
					cout << "\n\n\n\t\t\t\t\t\tNot found";
				}
            }
				break;
            
			case 4:{
				
            	cout << "\n\n\n\t\t\t\t\t\tEnter Genre: ";
                cin.ignore();
				getline(cin, g);	
				int j = SearchByGenre(root, g);

				if( j == 0){
					cout << "\n\n\n\t\t\t\t\t\tNot found";
				}
				break;
			}
			
            case 5:
            {
				int a =	SearchByRating(root);
            	
				if( a == 0){
					cout << "\n\n\n\t\t\t\t\t\tNot found";
				}	
				break;
			}
            	
            case 6: 
			{
			    cout << "\n\n\n\t\t\t\t\t\tEnter genre: ";
                cin.ignore();
				getline(cin, g2);
            	
            	int e = SearchByGenreRating2(root, g2);
            	
            	if(e == 0){
					cout << "\n\n\n\t\t\t\t\t\tNot found";	
				}
            	break;
		    }
			case 7:
		    {
        		cout << "\n\n\n\t\t\t\t\t\tEnter Movie ID: ";
				cin >> mi;

               	system("cls");

				string st = "D E L E T I N G  B Y  M O V I E  I D ";
	            m(st);
				
				if( deleteByMovieID(root, mi) !=NULL){
		        cout << "\n\n\n\t\t\t\t\t\t" << mi << " DELETED";		
				} 
				else{
					cout << "\n\n\n\t\t\t\t\t\tNot found\n";
				}
                break;
            }
            
			case 8:
            	cout << "\n\n\n\t\t\t\t\t\tTHE END\n";
                break;
            	
			default:
                cout << "\n\n\n\t\t\t\t\t\tINVALID INPUT";
                break;
        }
        
		cout << "\n\n\n\t\t\t\tEnter 1 to do it again, else enter 0: ";
        cin >> next;
        system("cls");
    }
    while(next!=0);

}
