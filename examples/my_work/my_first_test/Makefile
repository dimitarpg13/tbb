# Copyright (c) 2005-2019 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# GNU Makefile that builds and runs example.
run_cmd=
PROG=my_first_test_extended
ARGS=
LIGHT_PROG=my_first_test

# The C++ compiler
ifneq (,$(shell which icc 2>/dev/null))
CXX=icc
endif # icc

TBBLIB = -ltbb
TBBLIB_DEBUG = -ltbb_debug

ifneq (,$(findstring mic, $(offload)))
override CXXFLAGS += -qoffload-arch=$(offload) -qopt-report-phase:offload -D__TBB_MIC_OFFLOAD=1
# Replace -ltbb with -tbb in the offload mode
TBBLIB = -tbb
TBBLIB_DEBUG += -qoffload-option,mic,ld,"-ltbb_debug"
endif

ifeq ($(shell uname), Linux)
ifeq ($(target), android)
LIBS+= --sysroot=$(SYSROOT)
run_cmd=../../common/android.linux.launcher.sh
else
LIBS+= -lrt 
endif
else ifeq ($(shell uname), Darwin)
override CXXFLAGS += -Wl,-rpath,$(TBBROOT)/lib
endif

all:	release test

release: *.cpp
ifeq ($(offload),)
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o my_first_test my_first_test.cpp $(TBBLIB) $(LIBS)
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o my_first_test_extended my_first_test_extended.cpp $(TBBLIB) $(LIBS)
endif

debug: *.cpp
ifeq ($(offload),)
	$(CXX) -O0 -g -DTBB_USE_DEBUG $(CXXFLAGS) -o my_first_test my_first_test.cpp $(TBBLIB_DEBUG) $(LIBS)
	$(CXX) -O0 -g -DTBB_USE_DEBUG $(CXXFLAGS) -o my_first_test_extended my_first_test_extended.cpp $(TBBLIB_DEBUG) $(LIBS)
endif

clean:
	$(RM) my_first_test my_first_test_extended *.o *.d

test:
	$(run_cmd) ./$(PROG) $(ARGS)

light_test:
	$(run_cmd) ./$(LIGHT_PROG) $(ARGS)
