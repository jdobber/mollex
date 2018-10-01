project('mollex', 
	'cpp', 
	default_options : ['cpp_std=c++14'])

success = true

cc_args = [] #['-Wno-deprecated', '-pthread']

cc = meson.get_compiler('cpp')

# sources
#c = run_command('ls_sources.sh')
#sources = c.stdout().strip().split('\n')

sources = ['src/mollex.cxx',
	'src/detect.cxx',
	'src/molluscoid.cxx',
	'src/globals.cxx',
	]

# dependencies
deps = []
inc_dirs = []
libs = []

# Qt5
qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core'], required : true)
deps += qt5_dep

# OpenCV
cv_dep = dependency('opencv', version : ['>= 3.4.0'], required : false)
if cv_dep.found()
	deps += cv_dep
else
	message('Could not found OpenCV. Use custom paths instead: ')
	message('Includes: ' + get_option('opencv_includes'))
	message('Lib: ' + get_option('opencv_lib'))
  	deps += declare_dependency(
		include_directories:  
			include_directories( get_option('opencv_includes') ),
		link_args: get_option('opencv_lib')
	)	
endif

# openmp
#if cc.has_header('omp.h')  
#	cc_args += '-fopenmp'
#	deps += cc.find_library('gomp', required: true)
#endif

# Debug options
message(get_option('buildtype'))
if get_option('buildtype').startswith('debug')
	add_project_arguments('-DDEBUG', language : 'cpp')
endif

if host_machine.system() == 'windows'	
	add_project_arguments('-D_USE_MATH_DEFINES', language : 'cpp')
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