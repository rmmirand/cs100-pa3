subdir('bitStream')
subdir('encoder')

compress_exe = executable('compress.cpp.executable',
	sources: ['compress.cpp'],
	dependencies : [bit_stream_dep, bit_output_dep, hct_node_dep],
	install : true)

uncompress_exe = executable('uncompress.cpp.executable',
	sources: ['uncompress.cpp'],
	dependencies : [bit_stream_dep, bit_output_dep, hct_node_dep],
	install : true)

