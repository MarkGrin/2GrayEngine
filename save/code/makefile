build : out

out : main.cpp toTree.h
	g++ -std=c++0x main.cpp -o out 2> err.txt

main.cpp : ASTree.h ASTreeMethods.h ASTNode.h ASTNodeMethods.h toTree.h
