hct_node = library('hct_node', sources:['HCNode.hpp', 'HCTree.hpp', 'HCTree.cpp'], dependencies: [bit_stream_dep, bit_output_dep])

inc = include_directories('.')

hct_node_dep = declare_dependency(include_directories : inc, link_with: hct_node)
