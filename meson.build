project('mollex', 
	'cpp', 
	default_options : ['cpp_std=c++11'])

success = true

cc_args = ['-Wno-deprecated', '-pthread']

cc = meson.get_compiler('cpp')

# sources
#c = run_command('ls_sources.sh')
#sources = c.stdout().strip().split('\n')

sources = ['src/mollex.cxx',
	'src/detect.cxx',
	'src/molluscoid.cxx']

# dependencies
inc_dirs = []
deps = [	    
    dependency('threads'),
    dependency('opencv', version : ['>= 3.4.0'], required : true)
]

# openmp
if cc.has_header('omp.h')  
	cc_args += '-fopenmp'
	deps += cc.find_library('gomp', required: true)
endif

# Debug options
if get_option('buildtype').startswith('debug')
  add_project_arguments('-DDEBUG', language : 'cpp')
endif

if success
	executable('mollex', sources, 
		dependencies: deps, 
		include_directories: 
			include_directories(
				inc_dirs
			),
		cpp_args: cc_args )
endif