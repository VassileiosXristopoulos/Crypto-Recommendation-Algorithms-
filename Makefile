CC=g++ -std=c++11
CFLAGS=-Wall -g3 
LFLAGS= -g3 -o recommendation
OBJS=obj/recommendation.o obj/DataSetMap.o obj/Item.o obj/EucledianHashTable.o obj/hashFunction.o obj/HashNode.o obj/Util.o obj/cosineHashfunction.o obj/AHashTable.o obj/CosineHashTable.o obj/EucledianHypercube.o obj/CosineHypercube.o obj/CubeEdge.o obj/BinaryMap.o obj/AHypercube.o obj/ClusterMaster.o obj/Cluster.o obj/lsh.o obj/rangeSearch_consts.o obj/cube.o obj/Coin.o obj/Tweet.o obj/TwitterUserFactory.o obj/User.o obj/Predictor.o obj/Validator.o
MOVE=$(shell mv *.o obj)

all:recommendation

recommendation:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(MOVE)

obj/recommendation.o: src/recommendation.cpp
	$(CC) $(CFLAGS) -c src/recommendation.cpp

obj/Coin.o: src/recommendation/Coin.cpp
	$(CC) $(CFLAGS) -c src/recommendation/Coin.cpp

obj/Tweet.o: src/recommendation/Tweet.cpp
	$(CC) $(CFLAGS) -c src/recommendation/Tweet.cpp

obj/TwitterUserFactory.o: src/recommendation/TwitterUserFactory.cpp
	$(CC) $(CFLAGS) -c src/recommendation/TwitterUserFactory.cpp

obj/User.o: src/recommendation/User.cpp
	$(CC) $(CFLAGS) -c src/recommendation/User.cpp

obj/Predictor.o: src/recommendation/Predictor.cpp
	$(CC) $(CFLAGS) -c src/recommendation/Predictor.cpp

obj/Validator.o: src/recommendation/Validator.cpp
	$(CC) $(CFLAGS) -c src/recommendation/Validator.cpp

obj/ClusterMaster.o: src/clustering/ClusterMaster.cpp
	$(CC) $(CFLAGS) -c src/clustering/ClusterMaster.cpp

obj/Cluster.o: src/clustering/Cluster.cpp
	$(CC) $(CFLAGS) -c src/clustering/Cluster.cpp

obj/rangeSearch_consts.o: src/clustering/rangeSearch_consts.cpp
	$(CC) $(CFLAGS) -c src/clustering/rangeSearch_consts.cpp

obj/lsh.o: src/lsh/lsh.cpp
	$(CC) $(CFLAGS) -c src/lsh/lsh.cpp 

obj/DataSetMap.o: src/clustering/DataSetMap.cpp
	$(CC) $(CFLAGS) -c src/clustering/DataSetMap.cpp 

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
