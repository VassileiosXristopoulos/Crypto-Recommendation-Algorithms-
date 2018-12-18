CC=g++ -std=c++11
CFLAGS=-Wall -g3 
LFLAGS= -g3 -o cluster
OBJS=obj/cluster.o obj/DataSetMap.o obj/Item.o obj/EucledianHashTable.o obj/hashFunction.o obj/HashNode.o obj/Util.o obj/cosineHashfunction.o obj/AHashTable.o obj/CosineHashTable.o obj/EucledianHypercube.o obj/CosineHypercube.o obj/CubeEdge.o obj/BinaryMap.o obj/AHypercube.o obj/ClusterMaster.o obj/Cluster.o obj/lsh.o obj/rangeSearch_consts.o obj/cube.o
MOVE=$(shell mv *.o obj)

all:cluster

cluster:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(MOVE)

obj/cluster.o: src/cluster.cpp
	$(CC) $(CFLAGS) -c src/cluster.cpp

obj/ClusterMaster.o: src/ClusterMaster.cpp
	$(CC) $(CFLAGS) -c src/ClusterMaster.cpp

obj/Cluster.o: src/Cluster.cpp
	$(CC) $(CFLAGS) -c src/Cluster.cpp

obj/rangeSearch_consts.o: src/rangeSearch_consts.cpp
	$(CC) $(CFLAGS) -c src/rangeSearch_consts.cpp

obj/lsh.o: src/lsh/lsh.cpp
	$(CC) $(CFLAGS) -c src/lsh/lsh.cpp 

obj/DataSetMap.o: src/DataSetMap.cpp
	$(CC) $(CFLAGS) -c src/DataSetMap.cpp 

obj/Item.o: src/Item.cpp
	$(CC) $(CFLAGS) -c src/Item.cpp

obj/EucledianHashTable.o: src/lsh/EucledianHashTable.cpp
	$(CC) $(CFLAGS) -c src/lsh/EucledianHashTable.cpp

obj/hashFunction.o: src/lsh/hashFunction.cpp
	$(CC) $(CFLAGS) -c src/lsh/hashFunction.cpp

obj/HashNode.o: src/lsh/HashNode.cpp
	$(CC) $(CFLAGS) -c src/lsh/HashNode.cpp

obj/Util.o: src/Util.cpp
	$(CC) $(CFLAGS) -c src/Util.cpp

obj/cosineHashfunction.o: src/lsh/cosineHashfunction.cpp
	$(CC) $(CFLAGS) -c src/lsh/cosineHashfunction.cpp

obj/AHashTable.o: src/lsh/AHashTable.cpp
	$(CC) $(CFLAGS) -c src/lsh/AHashTable.cpp

obj/CosineHashTable.o: src/lsh/CosineHashTable.cpp
	$(CC) $(CFLAGS) -c src/lsh/CosineHashTable.cpp

obj/cube.o: src/hypercube/cube.cpp
	$(CC) $(CFLAGS) -c src/hypercube/cube.cpp

obj/EucledianHypercube.o: src/hypercube/EucledianHypercube.cpp
	$(CC) $(CFLAGS) -c src/hypercube/EucledianHypercube.cpp

obj/CosineHypercube.o: src/hypercube/CosineHypercube.cpp
	$(CC) $(CFLAGS) -c src/hypercube/CosineHypercube.cpp

obj/CubeEdge.o: src/hypercube/CubeEdge.cpp
	$(CC) $(CFLAGS) -c src/hypercube/CubeEdge.cpp

obj/BinaryMap.o: src/hypercube/BinaryMap.cpp
	$(CC) $(CFLAGS) -c src/hypercube/BinaryMap.cpp

obj/AHypercube.o: src/hypercube/AHypercube.cpp
	$(CC) $(CFLAGS) -c src/hypercube/AHypercube.cpp

clean:
	rm -f cluster $(OBJS)
