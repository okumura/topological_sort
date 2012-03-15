
function tsort(graph, on_resolved)
	visited = {}
	
	function visit(node, deps)
		v = visited[node]
		if v == "just" then
			return true
		elseif v == "once" then
			return false
		else
			visited[node] = "just"
			for k, v in pairs(deps) do
				if visit(v, graph[v]) then
					return true
				end
			end
			visited[node] = "once"
			on_resolved(node)
			return false
		end
	end
	
	for node, deps in pairs(graph) do
		if visit(node, deps) then
			return true
		end
	end
	
	return false
end

graphs = {
	graph1 = {
		lib1 = {'lib2'},
		lib2 = {'lib3'},
		lib3 = {},
	},
	
	graph2 = {
		lib1 = {'lib2'},
		lib2 = {'lib3'},
		lib3 = {'lib1'},
	}
}

for k, v in pairs(graphs) do
	print(k, tsort(v, print))
end
