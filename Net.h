#pragma once

#include "adj/GenericAdj.h"
#include "adj/AdjMat.h"
#include "exception/Exception.h"
#include <string>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <limits>
#include <set>
#include <functional>

using std::string;
using std::pair;
using std::vector;
using std::ostream;
using std::to_string;
using std::accumulate;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;
using std::set;
using std::exception;
using std::cerr;
using std::endl;

namespace BioNet {
	/// Network class
	/**
		Net class implements collection of nodes which are connected by edges.
		The connection can be unidirectional or bidirectional. Each edge has a 
		defined weight that must fall within the minimum and maximum allowed weight 
		for edges.	
	*/
	template<typename T>
	class Net {		
	private:
		/// The minimum weight allowed for edges
		T minweight;
		/// The maxium weight allowed for edges
		T maxweight;
		/// The base network class, created by AdjFactory for downcasting
		Adj<T>* network;
		/// A bool to determine if the network has unidirectional edges or not
		bool directed;
		/// A string for the type of network being implemented
		string networkType;

	public:
		/// Default constructor
		Net();

		Net(const T, const T, const bool = false, const string& = AdjMat<T>::NetworkType());
		Net(const Net<T>&);
		Net(Net<T>&&);
		~Net();

		void setRange(const T, const T);
		void setEdge(const unsigned int i, const unsigned int j, const T);
		void SetEdge(const string& n1, const string &n2, const T weight);
		void setNode(const unsigned int, const string &n);
		void deleteEdge(const unsigned int, const unsigned int);
		void deleteEdge(const string &l, const string &r);

		const T shortestPath(const int, const int) const;
		void resize(const int size);
		void clear();

		// Accessors
		const T getEdge(const int, const int) const;
		const string getNode(const int) const;
		const T getMinWeight() const { return minweight; }
		const T getMaxWeight() const { return maxweight; }
		const std::string & getNetworkType() const { return networkType; }

		//Operators
		const string & operator[](size_t index) const { return network->getNode(index); }
		const T operator()(size_t lhs, size_t rhs) const { return network->getEdge(lhs, rhs); }
		const T operator()(const string & lhs, const string & rhs) const { return network->getEdge(lhs, rhs); }

		const Net<T>& operator=(const Net& rhs);
		const bool operator==(const Net& rhs) const { return this->isEqual(rhs); }
		const bool operator!=(const Net& rhs) const { return !this->isEqual(rhs); }

		/// Assignment operator overload
		/**
		@param rhs Net class to set 'this' equal to
		*/
		template<class R>
		const Net<T>& operator=(const Net<R>& rhs)
		{
			minweight = rhs->minweight;
			maxweight = rhs->maxWeight;
			directed = rhs->directed;
			networkType = networkType;
			network->copy(rhs);
		}

		ostream& operator<<(ostream&) const;

		/// Overloaded operator+=
		/**
		@param rhs Net class to set 'this' equal to
		*/
		Net<T>* operator+=(const string& rhs)
		{
			network->addNode(rhs);
			return this;
		}

		/// Overloaded operator+
		/**
		@param rhs Net class to set 'this' equal to
		*/
		Net<T> operator+(const string& rhs)const
		{
			Net<T> bionet = *this;
			bionet.network->addNode(rhs);
			return bionet;
		}
		
		Net<T> operator*(const T)const;
		const Net<T>& operator*=(const T) const;

		Net<T> operator/(const T)const;
		const Net<T>& operator/=(const T) const;
		
		void convertToType(const string&);
		const T degree(const int) const;
		//void reserve(size_t);
		const size_t size() const;
		const unsigned int numberOfEdges() const;

	};

	// Moving All templated implementation to the Header so it works as expected	
	/// Constructor for Net class to create an unconnected network with a default range
	/**
	@param min Minimum weight value
	@param max Maximum weight value
	*/
	template<typename T>
	Net<T>::Net() : Net(-1.0, 1.0) {
		// for now start a default unconnected network with default range
		// The following code only creates a local version variable - Corrected by Dijkstra Team
		// Net(-1.0, 1.0);
	}

	/// Constructor for Net class
	/**
	@param min Minimum weight value
	@param max Maximum weight value
	@parm isDir Boolean determinng if network is unidirectional
	@param type The netwowrk type
	*/
	template<typename T>
	Net<T>::Net(const T min, const T max, const bool isDir, const string& type) {
		
		try {
			setRange(min, max);
			directed = isDir;
			networkType = type;
			network = AdjFactory::create<T>(networkType);
		}
		catch (const exception & e)
		{
			cerr << e.what() << endl;
			exit(0);
		}
	}

	/// Copy constructor for the Net class
	/**
	@param rhs Net class to copy
	*/
	template<typename T>
	Net<T>::Net(const Net<T>& rhs) {
		
		try {
			setRange(rhs.minweight, rhs.maxweight);
			directed = rhs.directed;
			networkType = rhs.networkType;
			network = AdjFactory::create(networkType);
			*network = *rhs.network;
		}
		catch (exception e)
		{
			cerr << e.what() << endl;
			AdjFactory::create(AdjMat::NetworkType());
			*network = *rhs.network;
		}
	}

	/// Move constructor for the Net class
	/**
	@param rhs Net class to move
	*/
	template<typename T>
	Net<T>::Net(Net<T>&& rhs) {
		setRange(rhs.minweight, rhs.maxweight);
		directed = rhs.directed;
		std::swap(networkType, rhs.networkType);
		network = std::move(rhs.network);
		rhs.~Net();
	}

	/// Destructor for the Net class
	/** Cleans up the network and all associated data inside
	*/
	template<typename T>
	Net<T>::~Net() {
		if (network != nullptr)
			delete network;
	}

	/// Sets the range of edge weights
	/**
	@param min Mininum value
	@param max Maximum value
	*/
	template<typename T>
	void Net<T>::setRange(const T min, const T max) {
		if (min > max)
		{
			throw Exception("mininum value is larger than maximum value");
		}
		minweight = min;
		maxweight = max;
	}

	/// Set Edge
	/**
	@param i origin node
	@param j destination node
	@param w weight, should be between mininum Weight and maximum Weight allowed
	*/
	template<typename T>
	void Net<T>::setEdge(const unsigned int i, const unsigned int j, const T w) {
		//Converting to a Network Class
		if (i < 0 || i > network->size())
			throw Exception("Node is not in the matrix range");

		if (j < 0 || j > network->size())
			throw Exception("Node is not in the matrix range");

		if (w < minweight || w > maxweight)
			throw Exception("Weight is not in the minWeight and maxWeight");
		try {
			network->setEdge(i, j, w);
			if (!directed) {
				network->setEdge(j, i, w);
			}
		}
		catch (exception e) {
			cerr << e.what() << endl;
		}
	}

	/// Set the edge from one node to another
	/*
	@param n1 origin node
	@param n2 destination node
	@param w weight, should be between minimum weight and maximum weight allowed
	*/
	template<typename T>
	void Net<T>::SetEdge(const string& n1, const string &n2, const T w)
	{
		if (w < minweight || w > maxweight)
			throw Exception("Weight is not in the minWeight and maxWeight");

		try {
			network->setEdge(n1, n2, w);
			if (!directed)
				network->setEdge(n2, n1, w);
		}
		catch (exception e) {
			cerr << e.what() << endl;
		}
		
	}

	/// Set the edge from one node to another
	/**
	@param i node, should be present in the matrix
	@param n name of the node
	*/
	template<typename T>
	void Net<T>::setNode(const unsigned int i, const string& n) {
		/// Converting to a Network Class
		if (i < 0 || i > network->size())
			throw Exception("Node is not in the matrix range");
		try{
			network->setNode(i, n);
		}
		catch (exception e) {
			cerr << e.what() << endl;
		}
	}

	// Accessors
	/// Returns an edge based off of given indices
	/**
	@param i first index
	@param j second index
	@return Edge between the secified nodes
	*/
	template<typename T>
	const T Net<T>::getEdge(const int i, const int j) const {
		///Converting to a Network Class
		if (i < 0 || i > network->size())
			throw Exception("Node is not in the matrix range");

		if (j < 0 || j > network->size())
			throw Exception("Node is not in the matrix range");
		try {
			return network->getEdge(i, j);
		}
		catch(exception e) {
			cerr << e.what() << endl;
		}		
	}

	/// Returns the name of a node from a given index
	/**
	@param i Index of the network to retrieve 
	@return Node at the specified index
	*/
	template<typename T>
	const string Net<T>::getNode(const int i) const {
		if (i < 0 || i > network->size())  // corrected from network.size()
			throw Exception("Node is not in the matrix range");
		try{
			return network->getNode(i);
		}
		catch (exception e) {
			cerr << e.what() << endl;
		}
	}

	/// Resizes the network based off of given size
	/**
	@param size new size the resize to
	*/
	template<typename T>
	void Net<T>::resize(const int size) {

		if (size <= 0)
			throw Exception("resize value is invalid");
		try {
			network->resize(size);
		}
		catch (exception e) {
			cerr << e.what() << endl;
		}
	}

	/// Resizes the network based off of given size
	/**
	@param size new size the resize to
	*/
	template<typename T>
	void Net<T>::clear() {
		//network->clear();
	}
	
	/// Converts the network to the given type
	/**
	@param type new type of the network
	*/
	template<typename T>
	void Net<T>::convertToType(const string& type)
	{
		try {
			auto old = network;
			network = AdjFactory::create(type);
			network->resize(old->size());
			for (int i{ 0 }; i < network->size(); i++)
			{
				network->setNode(i, old->getNode(i));
				for (int j{ 0 }; j < network->size(); j++)
					network->setEdge(i, j, old->getEdge(i, j));
			}
			networkType = type;
			delete old;
		}
		catch (exception e)
		{
			cerr << e.what() << "Error converting network to type " + type + ".\n" << endl;
		}

	}

	/// Network size accessor
	/** 
	@return the size of the network
	*/
	template<typename T>
	const size_t Net<T>::size() const
	{
		return network->size();
	}


	/*
	template<typename T>
	void BioNet<T>::reserve(size_t size)
	{
	if (size < 0)
	throw BioNetException("Size is negative!");
	network->reserve(size);
	}*/

	/// Network degree accessor
	/**
	@return the degree of the network
	*/
	template<typename T>
	const T Net<T>::degree(const int index) const {
		if (index < 0 || index >= network->size())
			throw Exception("Index out of bounds!");
		return network->degree(index);
	}

	/// Returns the shortest path between two nodes
	/**
	@param start The starting node index
	@param end The ending node index
	@return the shortest path between two nodes
	*/
	template<typename T>
	const T Net<T>::shortestPath(const int start, const int end) const {

		if (start < 0 || start > network->size())
			throw Exception("Start node is not in the matrix range");

		if (end < 0 || end > network->size())
			throw Exception("End node is not in the matrix range");

		T negativeEdges = 0;

		if (minweight < 0)
			negativeEdges = minweight * -1 + 1;

		vector<T> dist(network->size(), std::numeric_limits<T>::max());

		vector<int> prev(network->size(), -1);

		set<int> vertexSet;

		dist[start] = 0;

		for (int i = 0; i < network->size(); i++)
			vertexSet.insert(i);

		auto distFunct = bind([](vector<T>& d, int x, int y) {return d[x] < d[y]; }, dist, _1, _2);

		while (vertexSet.size())
		{
			auto current = *std::min_element(vertexSet.begin(), vertexSet.end(), distFunct);

			if (current == end)
				break;

			vertexSet.erase(current);

			for (int i = 0; i < network->size(); i++)
			{
				if (network->getEdge(current, i))
				{
					auto weight = negativeEdges ? network->getEdge(current, i) + negativeEdges : network->getEdge(current, i);

					auto alt = dist[current] + weight;

					if (alt < dist[i])
					{
						dist[i] = alt;
						prev[i] = current;
					}
				}
			}
		}

		if (dist[end] == std::numeric_limits<T>::max())
			throw Exception("No path found from start to end nodes.");

		T result = dist[end];
		int current = end;
		if (negativeEdges)
			while (prev[current] != -1)
			{
				current = prev[current];
				result -= negativeEdges;
			}
		return result;
	}

	/// Returns the number of edges in the network
	/**
	@return Number of edges in the network
	*/
	template<typename T>
	const unsigned int Net<T>::numberOfEdges() const {
		int x = network->numberOfEdges();
		if (!directed)
			x = x / 2;
		return x;
	}

	/// Deletes an edge between two nodes given the indices
	/**
	@param lval The first node index
	@param rval the second node index
	*/
	template<typename T>
	void Net<T>::deleteEdge(const unsigned int lval, const unsigned int rval) {
		network->deleteEdge(lval, rval);
	}

	/// Deletes an edge between two nodes given the node names
	/**
	@param lstr The first node name
	@param rstr the second node name
	*/
	template<typename T>
	void Net<T>::deleteEdge(const string& lstr, const string& rstr) {
		network->deleteEdge(lstr, rstr);
	}
	
	/// Overloaded assignment operator
	/**
	@param rhs Net object to set 'this' equal to
	*/
	template<typename T>
	const Net<T>& Net<T>::operator=(const Net<T>& rhs)
	{
		minweight = rhs.minweight;
		maxweight = rhs.maxweight;
		directed = rhs.directed;
		networkType = networkType;
		network->copy(rhs.network);

		return *this;
	}

	//template<typename T>
	//BioNet<T> BioNet<T>::operator+(const string& rhs) const
	//{
	//	BioNet retVal(*this);
	//	retVal.resize(network->size() + 1);
	//	retVal.setNode(network->size() - 1, rhs);
	//	return retVal;
	//}
	//
	//template<typename T>
	//const BioNet<T>& BioNet<T>::operator+=(const string& rhs) const
	//{
	//	network->resize(network->size() + 1);
	//	network->setNode(network->size() - 1, rhs);
	//	return *this;
	//}

	/// Overloaded shift operator
	/**
	@param os Network is assigned to output stream object
	*/
	template<typename T>
	ostream& Net<T>::operator<<(ostream& os) const
	{
		os << network;
		return os;
	}

	/// Overloaded operator *
	/**
	@param i Weight of the edges in the network are mutliplied by the given value
	*/
	template<typename T>
	Net<T> Net<T>::operator*(const T i)const
	{
		Net<T> retVal = this;
		retVal.network->scaleUp(i);
		return retVal;
	}

	/// Overloaded operator *=
	/**
	@param i Weight of the edges in the network are mutliplied by the given value
	*/
	template<typename T>
	const Net<T>& Net<T>::operator*=(const T i) const
	{
		network->scaleUp(i);
		return *this;
	}

	/// Overloaded operator /
	/**
	@param i Weight of the edges in the network are divided by the given value
	*/
	template<typename T>
	Net<T> Net<T>::operator/(const T i)const
	{
		Net<T> retVal = this;
		this->network->scaleDown(i);
		return retVal;
	}

	/// Overloaded operator /=
	/**
	@param i Weight of the edges in the network are divided by the given value
	*/
	template<typename T>
	const Net<T>& Net<T>::operator/=(const T i) const
	{
		network->scaleDown(i);
		return this;
	}

}


