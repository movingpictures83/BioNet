
#include "Adj.h"
#include "List.h"
#include "../exception/Exception.h"

#include <string>
#include <map>
#include <algorithm>
#include "../factory/Register.h"
using std::vector;
using std::string;
using std::map;
using std::find_if;

namespace BioNet {
	/// An Adjacency Basic for BioNet
	/**
	AdjBasic impements an adjacency Basic to represent the Bionet network.
	It consists of an array of nodes and an array of edges	*/
	template <typename T>
	struct BasicEdge
	{
		string source;
		string destination;
		T  weight;
	};

	template <typename T>
	class AdjBasic : public Adj<T>
	{
	public:
		
		string* arrBNodes;
		BasicEdge<T>* arrBEdges;
		int nTotalNodes;
		int nTotalEdges;
		int nCurNodes;
		int nCurEdges;
		static Register reg;
	
	private:
		void resizeEdge()
		{
			BasicEdge<T>* tempArrBEdges = new BasicEdge<T>[nTotalEdges << 1];
			for (int n = 0; n < nTotalEdges; n++)
			{
				tempArrBEdges[n] = arrBEdges[n];
			}

			nTotalEdges = nTotalEdges << 1;
			delete[] arrBEdges;
			arrBEdges = tempArrBEdges;

		}

	public:
		
		/// Used for factory Construction
		/**
		@return A new, dynamic instance of AdjList
		*/
		static GenericAdj* make()
		{
			return new AdjBasic<T>();
		}
		/// Specifies the type of the network used to register instances in the factory.
		/**
		@return Type name of the network.
		*/
		static const string& NetworkType()
		{
			static const type_info& ti = typeid(AdjBasic<T>);
			string keyword = ti.name();
			AdjFactory::mFactoryMap.find(keyword) == AdjFactory::mFactoryMap.end() ? Register(keyword, &AdjList::make) : reg;
			return keyword;
		}
		/// AdjList Copy constructor
		AdjBasic(const AdjBasic& copy)
		{
			network = vector<List<T>>(copy.network.size());
			for (size_t i = 0; i < copy.network.size(); i++)
				network[i] = List<T>(copy.network[i]);
		}
		/// AdjList constructor
		/**
		@param Initial size of the network
		*/
		AdjBasic(int i = 5) {
			arrBNodes = new string[i];
			arrBEdges = new BasicEdge<T>[i<<1];
			nTotalNodes = i;
			nTotalEdges = i << 1;
			nCurEdges = 0;
		}
		~AdjBasic() {}

		/// Set the edge between two nodes
		/**
		@param x index of the first node
		@param y index of the second node
		@param w weight of the edge
		*/
		void setEdge(const int x, const int y, const T w)
		{
			if ((x < 0 && x > nTotalNodes) || (y < 0 && y > nTotalNodes))
			{
				throw Exception("Node not found.");
				return;
			}
			
			string source = arrBNodes[x];
			string destination = arrBNodes[y];

			setEdge(source, destination, w);

			return;
		}

		/// Set the edge between two nodes
		/**
		@param x name of the first node
		@param y name of the second node
		@param w weight of the edge
		*/
		void setEdge(const string& x, const string& y, const T w)
		{
			if (nCurEdges >= nTotalEdges)
			{
				resizeEdge();				
			}	
			arrBEdges[nCurEdges].source = x;
			arrBEdges[nCurEdges].destination = y;
			arrBEdges[nCurEdges].weight = w;
			nCurEdges++;
		}

		/// gets the weight of the edge
		/**
		@param x index of the first node
		@param y index of the second node
		@return the weight of the edge
		*/
		T getEdge(const int x, const int y) const
		{
			double weight = 0.0;
			if ((x < 0 && x > nTotalNodes) && (y < 0 && y > nTotalNodes))
			{
				string source = arrBNodes[x];
				string destination = arrBNodes[y];

				weight = getEdge(source, destination);
			}
			return weight;
		}
		/// gets the weight of the edge
		/**
		@param a name of the first node
		@param b name of the second node
		@return the weight of the edge
		*/
		T getEdge(const string& a, const string& b) const
		{	
			double weight = 0.0;
			for (int nIdx = 0; nIdx < nTotalEdges; nIdx++)
			{
				BasicEdge<T> edge = arrBEdges[nIdx];
				if (strcmp(edge.source.c_str(), a.c_str()) == 0 && strcmp(edge.destination.c_str(), b.c_str()) == 0)
				{
					weight = edge.weight;
					break;
				}						
			}

			return weight;
		}

		/// sets the node in the network
		/**
		@param i index of the node
		@param s name of the node
		*/
		void setNode(const int i, const string& s)
		{
			if (i >= nTotalNodes)
			{
				resize(nTotalNodes << 1);
			}
			arrBNodes[i] = s;
			nCurNodes++;
		}

		/// gets the name of the node
		/**
		@param i index of the node
		@return the name of the node
		*/
		string getNode(const int i) const
		{
			return arrBNodes[i];
		}

		/// the size of the network
		/**
		@return the size of the network
		*/
		int size() const
		{
			return nCurNodes;
		}

		/// the degree of a node
		/**
		@param x the index of the node
		@return the total of the edges
		*/
		T degree(const int x) const
		{
			if (x < 0 || x > nCurNodes)
			{
				throw Exception("Node not found.");
			}
			string strNode = arrBNodes[x];

			T degree = 0.0;
			for (int nEdg = 0; nEdg < nCurEdges; nEdg++)
			{
				BasicEdge<T> edge = arrBEdges[nEdg];
			
				if (strcmp(edge.source.c_str(), strNode.c_str()) == 0 || strcmp(edge.destination.c_str(), strNode.c_str()) == 0)
				{
					degree += edge.weight;
				}
			}			
			return degree;
		}

		/// get the number of edges in the network
		/**
		@return the number of edges
		*/
		unsigned int numberOfEdges() const
		{
			return nCurEdges;
		}

		/// resize the AdjList
		/**
		@param newSize the new size of the network
		*/
		void resize(const int newSize)
		{
			// Resizing of Nodes array
			if (newSize > nTotalNodes)
			{
				string* tempArrBNodes = new string[newSize];
				for (int n = 0; n < nTotalNodes; n++)
				{
					tempArrBNodes[n] = arrBNodes[n];
				}
				
				nTotalNodes = newSize;
				delete[] arrBNodes;
				arrBNodes = tempArrBNodes;				
			}
		}

		
		/// find the index of a node
		/**
		Finds the index of a node or returns a BioNetException if not found.
		@param name the name of the node
		@return the index of the node
		*/
		int findNodeIndex(const string& name) const
		{
			for (int n = 0; n < nCurNodes; n++)
				if (strcmp(arrBNodes[n].c_str(), name.c_str()) == 0)
					return n;
			throw Exception("Node not found.");
			
			return 0;
		}

		/// delete an edge in the network
		/**
		@param x the name of the first node
		@param y the name of the second node
		*/
		void deleteEdge(const string & x, const string & y)
		{	
			BasicEdge<T>* tempArrBEdges = new BasicEdge<T>[nTotalEdges];
			int nCopied = 0;
			for (int nIdx = 0; nIdx < nCurEdges; nIdx++)
			{
				BasicEdge<T> edge = arrBEdges[nIdx];

				// When only Node is passed do not copy
				if ((strcmp(x.c_str(), y.c_str()) == 0) && (strcmp(edge.source.c_str(), x.c_str()) == 0 || strcmp(edge.destination.c_str(), x.c_str()) == 0))
				{
					// Dont copy when only Node is specified
				}
				else if ((strcmp(edge.source.c_str(), x.c_str()) == 0 && strcmp(edge.destination.c_str(), y.c_str()) == 0))
				{
					// Do not copy when you directly specify edge name
				}
				else
				{
					tempArrBEdges[nCopied] = edge;
					nCopied++;
				}
			}
			nCurEdges = nCopied;
			delete[] arrBEdges;
			arrBEdges = tempArrBEdges;
		}

		/// delete an edge in the network
		/**
		@param x the index of the first node
		@param y the index of the second node
		*/
		void deleteEdge(const int x, const int y)
		{
			if ((x < 0 && x > nCurNodes) && (y < 0 && y > nCurNodes))
			{
				string source = arrBNodes[x];
				string destination = arrBNodes[y];

				deleteEdge(source, destination);
			}
		}

		/// delete a node in the network
		/**
		@param name the name of the node to delete
		*/
		void deleteNode(const string & name)
		{
			int nNodeIndex = findNodeIndex(name);
			if (nNodeIndex >= 0 && nNodeIndex < nCurNodes)
				deleteNode(nNodeIndex);

			deleteEdge(name, name);
		}

		/// delete a node in the network
		/**
		@param index the index of the node to delete
		*/
		void deleteNode(const int index)
		{
			if(index < 0 || index > nCurNodes)
				throw Exception("Invalid Node Index specified");
			
			string* tempArrBNodes = new string[nTotalNodes];
			int nCopied = 0;
			for (int n = 0; n < nCurNodes; n++)
			{
				if (index != n) // Copy all elements from the index except which is to be deleted
				{
					tempArrBNodes[nCopied] = arrBNodes[n];
					nCopied++;
				}
			}

			nCurNodes = nCopied;
			delete[] arrBNodes;
			arrBNodes = tempArrBNodes;			
		}

		/// create a copy of the network
		/**
		@param rhs the Adj to copy
		*/
		void copy(const Adj<T>* rhs) {
			int test = rhs->size();
			int abc = 0;
			/*names.resize(rhs->size());
			for (unsigned i = 0; i < names.size(); i++) {
				names[i] = rhs->getNode(i);
			}
			matrix.resize(rhs->size());
			for (unsigned i = 0; i < rhs->size(); i++) {
				for (unsigned j = 0; j < rhs->size(); j++) {
					matrix[i][j] = (T)rhs->getEdge(i, j);
				}
			}*/

		}


		/// check if two networks are equal
		/**
		@param adj the network to compare
		*/
		bool isEqual(const Adj<T>* adj)
		{
		/*	auto _rhs = static_cast<const AdjBasic<T> *>(rhs);
			for (unsigned i = 0; i < nCurNodes; i++) {
				if (arrBNodes[i].compare(_rhs->))
					return false;*/
			return true;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		////ADD TEAM

		/// add a node to the network
		/**
		@param name the name of the node to add
		*/
		void addNode(const string& name)
		{
			nCurNodes++;
			setNode(nCurNodes, name);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		////EQUALS TEAM


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		////SCALE TEAM

		/// scale the network by a factor
		/**
		@param weight the factor to scale by
		*/
		void scaleUp(T weight) {
			for (int n = 0; n < nCurEdges; n++)
			{
				BasicEdge<T> edge = arrBEdges[n];
				edge.weight = edge.weight * weight;
			}
		}

		/// scale the network by a factor
		/**
		@param weight the factor to scale by
		*/
		void scaleDown(T weight) {
			for (int n = 0; n < nCurEdges; n++)
			{
				BasicEdge<T> edge = arrBEdges[n];
				edge.weight = edge.weight / weight;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	template<>
	BioNet::Register BioNet::AdjBasic<int>::reg = Register("BioAdjBasicInt", &AdjBasic<int>::make);
	template<>
	BioNet::Register BioNet::AdjBasic<float>::reg = Register("BioAdjBasicFloat", &AdjBasic<float>::make);
	template<>
	BioNet::Register BioNet::AdjBasic<double>::reg = Register("BioAdjBasicDouble", &AdjBasic<double>::make);
}

