#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 56
#define TEMP 0
#define PERM 1
#define FALSE 0
#define TRUE 1
#define infinity 9999

//void create_graph();
void display();
int maketree(struct edge tree[MAX],int *weight);
int all_perm(struct node state[MAX] );

struct node
{
	int predecessor;
	int dist; /*Distance from predecessor */
	int status;
};

struct edge
{
	int u;
	int v;
};

int adj[MAX][MAX];
int n = 56;
char *city[MAX] = {"Agrigento", "Alassio", "Ancona", "Aosta", "Arezzo", "Assisi", "Bari", "Bergamo", "Bologna", "Bolzano", "Caserta", "Catania", "Cervinia", "Como", "Cortina", "Cosenza", "Ferrara", "Florence", "Genoa", "L'Aquila", "Lecce", "Lucca", "Mantova", "Matera", "Messina", "Milan", "Modena", "Naples", "Ortisei", "Padua", "Palermo", "Parma", "Pavia", "Perugia", "Placenza", "Pisa", "Ravenna", "Reggio Calabria", "Rimini", "Roma", "Salerno", "Sanremo", "Sestriere", "Siena", "Siracusa", "Stresa", "Taormina", "Taranto", "Turin", "Trento", "Trieste", "Udine", "Venice", "Verona", "Vicenza", "Viterbo"};


int main()
{
	int i,j;
	int path[MAX];
	int wt_tree,count;
	struct edge tree[MAX];

	adj[0][30] = 136;
	adj[1][50] = 634;
	adj[1][8] = 383;
	adj[1][9] = 497;
	adj[1][17] = 366;
	adj[1][18] = 98;
	adj[1][25] = 248;
	adj[1][48] = 167;
	adj[1][52] = 485;
	adj[1][39] = 624;
	adj[2][6] = 475;
	adj[2][8] = 210;
	adj[2][9] = 479;
	adj[2][17] = 255;
	adj[2][18] = 495;
	adj[2][25]= 428;
	adj[2][27]=410;
	adj[2][52]=335;
	adj[2][39]=294;
	adj[2][48]=548;
	adj[2][50]=484;
	adj[3 ][50] =564;
	adj[3 ][8]= 390;
	adj[3 ][9]= 451;
	adj[3 ][17]= 526;
	adj[3 ][18]= 256;
	adj[3 ][25 ]=182;
	adj[3 ][48 ]=126;
	adj[3 ][52]= 466;
	adj[4 ][6]= 691;
	adj[4 ][8 ]=191;
	adj[4 ][9 ]=482;
	adj[4 ][17]= 85;
	adj[4 ][18]= 353;
	adj[4 ][25]= 409;
	adj[4 ][27 ]=478;
	adj[4 ][52 ]=350;
	adj[4 ][39]= 246;
	adj[4 ][48]= 527;
	adj[4 ][50]= 499;
	adj[5 ][6 ]=596;
	adj[5 ][8]= 296;
	adj[5 ][9 ]=587;
	adj[5 ][17 ]=190;
	adj[5 ][18 ]=458;
	adj[5 ][25 ]=514;
	adj[5 ][27 ]=407;
	adj[5 ][52 ]=411;
	adj[5 ][39 ]=175;
	adj[5 ][48 ]=632;
	adj[5 ][50 ]=560;
	adj[6 ][20 ]=154;
	adj[6 ][33 ]=612;
	adj[6 ][38 ]=568;
	adj[6 ][8 ]=681;
	adj[6 ][55 ]=563;
	adj[6 ][23 ]=66;
	adj[6 ][46 ]=526;
	adj[6 ][36 ]=620;
	adj[6 ][27]= 322;
	adj[6 ][30]= 734;
	adj[6 ][39]= 482;
	adj[6 ][47 ]=87;
	adj[6 ][43 ]=714;
	adj[6 ][24 ]=476;
	adj[6 ][37 ]=490;
	adj[6 ][10 ]=350;
	adj[6 ][11 ]=572;
	adj[6 ][26 ]=720;
	adj[6 ][40 ]=269;
	adj[6 ][44 ]=648;
	adj[6 ][15 ]=271;
	adj[6 ][16 ]=694;
	adj[6 ][19 ]=424;
	adj[7 ][50]= 374;
	adj[7 ][8]= 229;
	adj[7 ][9]= 230;
	adj[7 ][17]= 335;
	adj[7 ][18]= 214;
	adj[7 ][25]= 58;
	adj[7 ][48]= 181;
	adj[7 ][52]= 238;
	adj[7 ][39]= 637;
	adj[8 ][55]= 321;
	adj[8 ][9 ]=291;
	adj[8 ][17]= 106;
	adj[8 ][18]= 285;
	adj[8 ][25]= 218;
	adj[8 ][27]= 640;
	adj[8 ][54]= 155;
	adj[8 ][39]= 408;
	adj[8 ][48]= 338;
	adj[8 ][50]= 308;
	adj[8 ][52]= 269;
	adj[8 ][10 ]=619;
	adj[8 ][51 ]=276;
	adj[8 ][12 ]=393;
	adj[8 ][13 ]=266;
	adj[8 ][14 ]=308;
	adj[8 ][45 ]=297;
	adj[8 ][16 ]=47;
	adj[8 ][19 ]=423;
	adj[8 ][53 ]=141;
	adj[8 ][21 ]=142;
	adj[8 ][22 ]=111;
	adj[8 ][23 ]=474;
	adj[8 ][49 ]=233;
	adj[8 ][26 ]=39;
	adj[8 ][28 ]=327;
	adj[8 ][29 ]=122;
	adj[8 ][31 ]=90;
	adj[8 ][32 ]=203;
	adj[8 ][33 ]=270;
	adj[8 ][34 ]=150;
	adj[8 ][35 ]=162;
	adj[8 ][36 ]=77;
	adj[8 ][43 ]=176;
	adj[8 ][38 ]=113;
	adj[8 ][40 ]=693;
	adj[8 ][41]= 431;
	adj[8 ][42 ]=416;
	adj[9 ][55 ]=618;
	adj[9 ][41 ]=545;
	adj[9 ][17 ]=397;
	adj[9 ][18 ]=399;
	adj[9 ][25 ]=276;
	adj[9 ][38 ]=382;
	adj[9 ][54 ]=154;
	adj[9 ][39 ]=90;
	adj[9 ][48 ]=408;
	adj[9 ][50 ]=338;
	adj[9 ][52 ]=225;
	adj[9 ][43 ]=467;
	adj[9 ][51 ]=283;
	adj[9 ][12 ]=454;
	adj[9 ][13 ]=283;
	adj[9 ][14 ]=109;
	adj[9 ][45 ]=347;
	adj[9 ][16 ]=256;
	adj[9 ][19 ]=692;
	adj[9 ][53 ]=150;
	adj[9 ][21 ]=413;
	adj[9 ][22 ]=189;
	adj[9 ][42 ]=500;
	adj[9 ][49 ]=58;
	adj[9 ][26 ]=252;
	adj[9 ][28 ]=39;
	adj[9 ][29 ]=188;
	adj[9 ][31]= 256;
	adj[9 ][32]= 278;
	adj[9 ][33]= 561;
	adj[9 ][34 ]=257;
	adj[9 ][35 ]=434;
	adj[9 ][36 ]=330;
	adj[10] [27]= 28;
	adj[10] [17]= 513;
	adj[10] [18]= 737;
	adj[10] [39]= 211;
	adj[11] [30]= 253;
	adj[11] [27]= 649;
	adj[12] [50]= 597;
	adj[12] [17]= 529;
	adj[12] [18]= 259;
	adj[12] [25]= 185;
	adj[12] [48]= 129;
	adj[12 ][52]= 461;
	adj[13 ][50]= 430;
	adj[13 ][17]= 372;
	adj[13 ][18]= 205;
	adj[13 ][25]= 48;
	adj[13 ][48]= 171;
	adj[13 ][52]= 294;
	adj[13 ][39]= 674;
	adj[14 ][50]= 225;
	adj[14 ][17]= 414;
	adj[14 ][18]= 500;
	adj[14 ][25]= 377;
	adj[14 ][48]= 509;
	adj[14 ][52]= 165;
	adj[14 ][39]= 716;
	adj[15 ][39]= 580;
	adj[15 ][27]= 348;
	adj[15 ][30]= 463;
	adj[16 ][17]= 153;
	adj[16 ][18 ]=321;
	adj[16 ][25 ]=245;
	adj[16 ][27 ]=687;
	adj[16 ][52 ]=112;
	adj[16 ][39 ]=455;
	adj[16 ][48 ]=381;
	adj[16 ][50 ]=261;
	adj[17 ][55 ]=221;
	adj[17 ][41 ]=414;
	adj[17 ][51 ]=382;
	adj[17 ][53 ]=247;
	adj[17 ][18]= 268;
	adj[17 ][25]= 324;
	adj[17 ][27]= 534;
	adj[17 ][54]= 261;
	adj[17 ][39 ]=302;
	adj[17 ][48 ]=442;
	adj[17 ][50 ]=414;
	adj[17 ][52 ]=265;
	adj[17 ][19 ]=352;
	adj[17 ][45 ]=403;
	adj[17 ][21 ]=72;
	adj[17 ][22 ]=217;
	adj[17 ][42 ]=522;
	adj[17 ][49  ]= 339;
	adj[17 ][49 ]= 339;
	adj[17 ][49 ]= 339;
	adj[17 ][49 ]=339;
	adj[17 ][26 ]=145;
	adj[17 ][28 ]=433;
	adj[17 ][29 ]=228;
	adj[17 ][31]= 196;
	adj[17 ][32 ]=309;
	adj[17 ][33 ]=164;
	adj[17 ][34 ]=256;
	adj[17 ][35 ]=92;
	adj[17 ][36 ]=136;
	adj[17 ][43 ]=70;
	adj[17 ][38 ]=158;
	adj[17 ][40 ]=587;
	adj[18 ][55 ]=447;
	adj[18 ][41 ]=146;
	adj[18 ][51 ]=504;
	adj[18 ][53 ]=282;
	adj[18 ][25 ]=156;
	adj[18 ][38 ]=398;
	adj[18 ][54 ]=332;
	adj[18 ][39 ]=526;
	adj[18 ][48 ]=174;
	adj[18 ][50 ]=336;
	adj[18 ][52 ]=387;
	adj[18 ][19 ]=598;
	adj[18 ][45 ]=215;
	adj[18 ][21 ]=193;
	adj[18 ][22 ]=243;
	adj[18 ][42 ]=252;
	adj[18 ][49 ]=341;
	adj[18 ][26 ]=246;
	adj[18 ][28 ]=435;
	adj[18 ][29 ]=350;
	adj[18 ][31 ]=195;
	adj[18 ][32 ]=121;
	adj[18 ][33 ]=432;
	adj[18 ][34 ]=142;
	adj[18 ][35 ]=190;
	adj[18 ][36 ]=362;
	adj[18 ][43 ]=296;;
	adj[19 ][25 ]=641;
	adj[19 ][27 ]=261;
	adj[19 ][52 ]=548;
	adj[19 ][39 ]=144;
	adj[19 ][50 ]=697;
	adj[20 ][27 ]=449;
	adj[20 ][39 ]=636;
	adj[20 ][30 ]=752;
	adj[21 ][50 ]=449;
	adj[21 ][25 ]=293;
	adj[21 ][27 ]=567;
	adj[21 ][52 ]=300;
	adj[21 ][39 ]=335;
	adj[21 ][48 ]=367;
	adj[22 ][50 ]=293;
	adj[22 ][25 ]=153;
	adj[22 ][48 ]=289;
	adj[22 ][52 ]=144;
	adj[22 ][39 ]=519;
	adj[23 ][39 ]=523;
	adj[23 ][30 ]=668;
	adj[23 ][27 ]=291;
	adj[24 ][30 ]=258;
	adj[24 ][27 ]=533;
	adj[25 ][55 ]=545;
	adj[25 ][41 ]=296;
	adj[25 ][43 ]=394;;
	adj[25 ][51 ]=384;
	adj[25 ][45 ]=79;
	adj[25 ][53 ]=164;
	adj[25 ][42 ]=231;
	adj[25 ][49 ]=218;
	adj[25 ][38 ]=331;
	adj[25 ][54 ]=214;
	adj[25 ][39 ]=626;
	adj[25 ][48 ]=139;
	adj[25 ][50 ]=420;
	adj[25 ][52 ]=284;
	adj[25 ][26 ]=179;
	adj[25 ][28 ]=312;
	adj[25 ][29 ]=247;
	adj[25 ][31 ]=128;
	adj[25 ][32 ]=35;
	adj[25 ][33 ]=488;
	adj[25 ][34 ]=68;
	adj[25 ][35 ]=290;
	adj[25 ][36 ]=295;
	adj[26 ][27 ]=679;
	adj[26 ][52 ]=187;
	adj[26 ][39 ]=447;
	adj[26 ][48 ]=299;
	adj[26 ][50 ]=336;
	adj[27 ][33 ]=408;
	adj[27 ][35 ]=568;
	adj[27 ][31 ]=730;
	adj[27 ][37 ]=567;
	adj[27 ][44 ]=725;
	adj[27 ][55 ]=313;
	adj[27 ][43 ]=464;
	adj[27 ][47 ]=365;
	adj[27 ][46 ]=603;
	adj[27 ][38 ]=503;
	adj[27 ][36 ]=555;
	adj[27 ][40 ]=53;
	adj[27 ][39 ]=232;
	adj[28 ][50 ]=300;
	adj[28 ][48 ]=444;
	adj[28 ][52 ]=219;
	adj[28 ][39 ]=735;
	adj[29 ][50 ]=186;
	adj[29 ][48 ]=378;
	adj[29 ][52 ]=37;
	adj[29 ][39]= 530;
	adj[30 ][47 ]=668;
	adj[30 ][37 ]=272;
	adj[30 ][46 ]=266;
	adj[30 ][44 ]=322;
	adj[31 ][50 ]=360;
	adj[31 ][52 ]=211;
	adj[31 ][39 ]=498;
	adj[31 ][48 ]=248;
	adj[32 ][50 ]=436;
	adj[32 ][48 ]=136;
	adj[32 ][52 ]=287;
	adj[32 ][39 ]=611;
	adj[33 ][52 ]=394;
	adj[33 ][39 ]=176;
	adj[33 ][48 ]=606;
	adj[33 ][50 ]=543;
	adj[34 ][50 ]=394;
	adj[34 ][48 ]=188;
	adj[34 ][52 ]=24;
	adj[34 ][39 ]=558;
	adj[35 ][50 ]=470;
	adj[35 ][52 ]=321;
	adj[35 ][39 ]=334;
	adj[35 ][48 ]=366;
	adj[36 ][52 ]=186;
	adj[36 ][39 ]=375;
	adj[36 ][48 ]=415;
	adj[36 ][50 ]=335;
	adj[38 ][52]= 238;
	adj[38 ][39 ]=337;
	adj[38 ][48 ]=451;
	adj[38 ][50 ]=387;
	adj[39 ][55 ]=81;
	adj[39 ][53 ]=549;
	adj[39 ][51 ]=684;
	adj[39 ][45 ]=705;
	adj[39 ][49 ]=641;
	adj[39 ][54 ]=563;
	adj[39 ][47 ]=569;
	adj[39 ][48 ]=702;
	adj[39 ][50 ]=715;
	adj[39 ][52 ]=567;
	adj[39 ][40 ]=285;
	adj[39 ][41 ]=672;
	adj[39 ][43]= 232;
	adj[41 ][50 ]=682;
	adj[41 ][48 ]=212;
	adj[41 ][52 ]=533;
	adj[42 ][50 ]=643;
	adj[42 ][48 ]=92;
	adj[42 ][52 ]=507;
	adj[43 ][52 ]=335;
	adj[43 ][48 ]=470;
	adj[43 ][50 ]=484;
	adj[45 ][50 ]=491;
	adj[45 ][48 ]=132;
	adj[45 ][52 ]=355;
	adj[48 ][55 ]=621;
	adj[48 ][51 ]=515;
	adj[48 ][49 ]=349;
	adj[48 ][53 ]=295;
	adj[48 ][50 ]=551;
	adj[48 ][54 ]=345;
	adj[48 ][52 ]=415;
	adj[49 ][50 ]=279;
	adj[49 ][52 ]=167;
	adj[50 ][55 ]=635;
	adj[50 ][51 ]=68;
	adj[50 ][52 ]=165;
	adj[50 ][53 ]=256;
	adj[50 ][54 ]=206;
	adj[51 ][52 ]=133;
	adj[52 ][55 ]=486;
	adj[52 ][53 ]=120;
	adj[52 ][54 ]=70;

	for(i=0; i<MAX; i++){
		for(j=0; j<MAX; j++){
			adj[j][i] = adj[i][j];
		}
	}

	for(i=0; i<MAX; i++){
		for(j=0; j<MAX; j++){
			if(adj[i][j] < 0) adj[i][j] = 0;
		}
	}

	/*create_graph();*/
	printf("Adjacency matrix is :\n");
	display();

	count = maketree(tree,&wt_tree);

	printf("\n\nWeight of spanning tree is (COST of the MST) : %d\n", wt_tree);
	printf("Edges to be included in spanning tree are : \n");
	for(i=1;i<=count;i++)
	{
		printf("%d->",tree[i].u);
		printf("%d\n",tree[i].v);
	}
	return 0;
}/*End of main()*/

/*void create_graph()
{
	int i, max_edges,origin,destin,wt;

	//printf("Enter number of vertices : ");
	//scanf("%d",&n);
	n = MAX;
	max_edges=n*(n-1)/2;
	/*
	for(i=1;i<=max_edges;i++)
	{
		printf("Enter edge %d(0 0 to quit) : ",i);
		scanf("%d %d",&origin,&destin);
		if((origin==0) && (destin==0))
			break;
		printf("Enter weight for this edge : ");
		scanf("%d",&wt);
		if( origin > n || destin > n || origin<=0 || destin<=0)
		{
			printf("Invalid edge!\n");
			i--;
		}
		else
		{
			adj[origin][destin]=wt;
			adj[destin][origin]=wt;
		}
	}*//*End of for*/
	/*if(i<n-1)
	{
		printf("Spanning tree is not possible\n");
		exit(1);
	}
}*//*End of create_graph()*/

void display()
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%5d",adj[i][j]);
		printf("\n");
	}
}/*End of display()*/

int maketree(struct edge tree[MAX],int *weight)
{
	struct node state[MAX];
	int i,k,min,count,current,newdist;
	int m;
	int u1,v1;
	*weight=0;
	/*Make all nodes temporary*/
	for(i=1;i<n;i++)
	{
		state[i].predecessor=0;
		state[i].dist = infinity;
		state[i].status = TEMP;
	}
	/*Make first node permanent*/
	state[0].predecessor=0;
	state[0].dist = 0;
	state[0].status = PERM;

	/*Start from first node*/
	current=0;
	count=0; /*count represents number of nodes in tree */
	while( all_perm(state) != TRUE ) /*Loop till all the nodes become PERM*/
	{
		for(i=1;i<n;i++)
		{
			if ( adj[current][i] > 0 && state[i].status == TEMP )
			{
				if(  adj[current][i] < state[i].dist )
				{
					state[i].predecessor = current;
					state[i].dist = adj[current][i];
				}
			}
		}/*End of for*/

		/*Search for temporary node with minimum distance
		and  make it current node*/
		min=infinity;
		for(i=1;i<n;i++)
		{
			if(state[i].status == TEMP && state[i].dist < min)
			{
				min = state[i].dist;
				current=i;
			}
		}/*End of for*/

		state[current].status=PERM;

		/*Insert this edge(u1,v1) into the tree */
		u1=state[current].predecessor;
		v1=current;
		count++;
		tree[count].u=u1;
		tree[count].v=v1;
		/*Add wt on this edge to weight of tree	*/
		*weight=*weight+adj[u1][v1];
	}/*End of while*/
	return (count);
}/*End of maketree()*/

/*This function returns TRUE if all nodes are permanent*/
int all_perm(struct node state[MAX] )
{
	int i;
	for(i=1;i<n;i++)
	   if( state[i].status == TEMP )
	       return FALSE;
	return TRUE;
}