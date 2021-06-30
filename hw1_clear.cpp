#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class node{
	
	public:
		unsigned int sendTo(int dstID); //return next node
		void bulid_routingTable(int distance[], vector< list<int> > AdjList, int nodeCnt);
		unsigned int id; //�Ӹ`�I��ID
		void printRoutingTable(int nodeCnt);
		
	private: 
		unsigned int routingTable[100]; //�C���I��routing table 
		
};

unsigned int node::sendTo(int dstID)
{
	return routingTable[dstID]; 
}

void node::bulid_routingTable(int distance[], vector< list<int> > AdjList, int nodeCnt)
{
	list<int>::iterator itr;
	int flag = 0, i, j;
	
	for(i=0; i<nodeCnt; i++){
		
		if(0 == distance[i]){   
			routingTable[i] = 0;
		}
		
		else if(1 == distance[i]){
			routingTable[i] = i; 
		}
		//�p�G��order�@�˪�ID�A��ID�s���̤p�� 
		else if(1 < distance[i]){
			int dist = distance[i], tmp = i;
			while(1 < dist){
				dist--;
				for(j=0; j<nodeCnt; j++){
					if(distance[j] == dist){
						//�P�_ j ���S���b tmp �� AdjList ��
						for(itr = AdjList[tmp].begin(); itr != AdjList[tmp].end(); itr++){  
							if(*itr == j){ flag = 1; break; } //���ӰO���Abreak�X�� 
						}
					}
					if(flag == 1) break;  //�p�Gflag��1�A���j���btmp��AdjList�� 
				}flag = 0;
				tmp = j;
			}
			routingTable[i] = j;
		}
		
	}
}

void node::printRoutingTable(int nodeCnt)
{
	for(int i=0; i<nodeCnt; i++){
		cout << routingTable[i] << " ";
	}cout << endl;
}

class Graph{
	
	public:
    Graph():num_vertex(0){};           // default constructor
    Graph(int nodeCnt);								// constructor with input: number of vertex
    void AddEdgeList(int node1, int node2);
    void BFS(int Start);
		int *color,             // 0:�զ�(�S��L), 1:�Ǧ�(�Q��L), 2:�¦�(queue.pop)
        *distance,          // 0:�_�I, �L���j:�q�_�I�����쪺vertex
        *predecessor;       // -1:�S��predecessor, ��ܬ��_�Ivertex
    vector< list<int> > AdjList;
		void displayAdjList();
		
	private:
    int num_vertex;
    
};

Graph::Graph(int nodeCnt): num_vertex(nodeCnt)
{     // constructor with input: number of vertex
      // initialize Adjacency List
    	AdjList.resize(num_vertex);
};

void Graph::AddEdgeList(int node1, int node2)
{
    AdjList[node1].push_back(node2);
    AdjList[node2].push_back(node1);
}

void Graph::BFS(int Start)
{
    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    distance = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++) {  // ��l��
        color[i] = 0;                       // 0:�զ�;
        predecessor[i] = -1;                // -1��ܨS��predecessor
        distance[i] = num_vertex+1;         // num_vertex��vertex, 
    }                                       // �̪��Z�� distance = num_vertex -1��edge

    queue<int> q;
    int i = Start;

    for (int j = 0; j < num_vertex; j++) {  // j�q0�ƨ�num_vertex-1, �]��j�|���Lgraph���Ҧ�vertex
        if (color[i] == 0) {                // �Ĥ@��i�|�O�_�Ivertex, �p�ϤG(c)
            color[i] = 1;                   // 1:�Ǧ�
            distance[i] = 0;                // �C�@��connected component���_�I���Z���]��0
            predecessor[i] = -1;            // �C�@��connected component���_�I�S��predecessor
            q.push(i);
            while (!q.empty()) {
                int u = q.front();                  // u ���s���j�M�_�I
                for (list<int>::iterator itr = AdjList[u].begin(); itr != AdjList[u].end(); itr++) {                         // ������q
                    if (color[*itr] == 0) {                // �Y�Q�u���v��vertex�O�զ�
                        color[*itr] = 1;                   // ��Ǧ�, ��ܤw�g�Q�u���v
                        distance[*itr] = distance[u] + 1;  // �Z���Opredecessor���Z���[�@
                        predecessor[*itr] = u;             // ��s�Q�u���v��vertex��predecessor
                        q.push(*itr);                      // ��vertex���iqueue
                    }
                }
                q.pop();        // ��u���Xqueue
                color[u] = 2;   // �åB��u��¦�
            }
        }
        // �Y�@���^��S����Ҧ�vertex���L, ���graph���h��connected component
        // �N��i�t��j, �~���ˬdgraph������Lvertex�O�_���O�զ�, �Y�O, ����while loop
        i = j;
    }
}

void Graph::displayAdjList(){
	
   for(int i = 0; i<num_vertex; i++) {
   	
      cout << i << "--->";
      list<int> :: iterator it;
      for(it = AdjList[i].begin(); it != AdjList[i].end(); ++it) {
         cout << *it << " ";
      }
      cout << endl;
   }
   
}

int main()
{
	unsigned int nodeCnt = 0, edgeCnt = 0, cnt = 0, ith_edge = 0, output = 0, ith_output = 0;
	unsigned int Node1, Node2, srcID[100] = {0}, dstID[100] = {0};
	
	cin >> nodeCnt >> edgeCnt;
	
	Graph g1(nodeCnt); //build Graph to do bfs
	while(cnt < edgeCnt-1)
	{
			cin >> ith_edge >> Node1 >> Node2;
			g1.AddEdgeList(Node1, Node2);
			cnt = ith_edge;
	}cnt = 0;
	
	//get output//
	cin >> output;
	while(cnt < output){
		cin >> ith_output >> srcID[cnt] >> dstID[cnt]; //cout << ith_output << " " << srcID[cnt] << " " << dstID[cnt] << endl;
		cnt++;
	}cnt = 0;
	
	node NodeList[nodeCnt]; //�إ�NodeList�A�C�ӽs�������C��Node�A�C��Node���ۤv��routingTable 
	while(cnt < nodeCnt){
		g1.BFS(cnt);	//��C���I��BFS
		NodeList[cnt].id = cnt;    //�ᤩ�`�I��ID 
		NodeList[cnt].bulid_routingTable(g1.distance, g1.AdjList, nodeCnt); //�ǤJg1.distance�Ag1.AdjList�إ�routingTable
		cnt++;
	}cnt = 0;
	
	while(cnt < output){
		unsigned int curID = srcID[cnt];
		cout << cnt << " " << srcID[cnt] << " ";
		while(curID != dstID[cnt]){
			curID = NodeList[curID].sendTo(dstID[cnt]);
			cout << curID << " ";
		}cout << endl;
		cnt++;
	}cnt = 0;
	
	return 0;
}
