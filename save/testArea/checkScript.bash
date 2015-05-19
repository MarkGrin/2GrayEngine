./scriptToAst.prog $1 check.tree
./dotter.prog check.tree || true
ristretto Graph.jpg
read
./astToExec.prog check.tree check.exec
read
./proc.prog check.exec
