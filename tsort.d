import std.stdio;

template TopologicalSort(T) {
	bool sort(T[][T] graph, void delegate(T) on_resolved) {
		bool[T] visited_whole;
		
		bool visit(T node, T[] deps, bool[T] visited) {
			if (node in visited) {
				return true;
			} else if (node in visited_whole) {
				return false;
			} else {
				visited[node] = true;
				visited_whole[node] = true;
				foreach (T dep; deps) {
					if (visit(dep, graph[dep], visited)) {
						return true;
					}
				}
				on_resolved(node);
				return false;
			}
		}
		
		foreach (T node, T[] deps; graph) {
			bool[T] visited;
			if (visit(node, deps, visited)) {
				return true;
			}
		}
		
		return false;
	}
}

void main() {
	alias string[][string] Graph;
	
	Graph graph1 = [
		"lib1": ["lib2"],
		"lib2": ["lib3"],
		"lib3": [],
	];
	
	Graph graph2 = [
		"lib1": ["lib2"],
		"lib2": ["lib3"],
		"lib3": ["lib1"],
	];
	
	foreach (Graph graph; [graph1, graph2]) {
		bool cyclic = TopologicalSort!(string).sort(
			graph,
			delegate(string node) {
				writefln("%s", node);
			});
		writefln(cyclic ? "cyclic" : "acyclic");
	}
}

