#!/usr/bin/env ruby

# topological sort with detection
# http://en.wikipedia.org/wiki/Topological_sorting

def visit(graph, node, deps, visited, &block)
  v = visited[node]
  if v == :just
    return true
  elsif v == :once
    return false
  else
    visited[node] = :just
    deps.each do |dep|
      if visit(graph, dep, graph[dep], visited, &block)
        return true
      end
    end
    visited[node] = :once
    block.call(node)
  end
end

def tsort(graph, &block)
  visited = {}
  
  graph.each_pair do |node, deps|
    return true if visit(graph, node, deps, visited, &block)
  end
  
  return false
end

test_data = {
  :graph1 => {
    'a' => ['b'],
    'b' => ['c'],
    'c' => [],
  },

  :graph2 => {
    'a' => [],
    'b' => [],
    'c' => ['a', 'b'],
  },

  :graph3 => {
    'a' => ['a'],
  },

  :graph4 => {
    'a' => ['b'],
    'b' => ['c'],
    'c' => ['a'],
  },

  :graph5 => {
    'a' => ['b', 'c'],
    'b' => ['a', 'c'],
    'c' => ['a', 'b'],
  },

}

test_data.each_pair do |name, graph|
  puts "#{name.to_s}"
  print "  in  : "; p graph

  print "  out : "
  cyclic = tsort(graph) do |node|
    print "#{node} -> "
  end
  print "\n"
  puts cyclic ? "  cyclic" : "  asyclic"
end
