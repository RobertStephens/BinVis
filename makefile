#
#  Copyright (c) 2011 Robert Stephens 
#
#  This file is part of BinVis.
#
#  BinVis is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  BinVis is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with BinVis.  If not, see <http://www.gnu.org/licenses/>.
#

CPP_FILES := hilbert.cpp pixel_assign.cpp pixel_generator.cpp
CPP_OBJS :=  $(CPP_FILES:%.cpp=%.o)

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CPP_FLAGS := -g3 -DDEBUG
else
    CPP_FLAGS := -O3 -DNDEBUG
endif


CPP := g++

INCLUDE := -L/usr/local/include `libpng-config --cflags`
LINK_FLAGS := -L/usr/local/lib `libpng-config --ldflags`

PNG++VER := 0.2.5

%.o: %.cpp
	@echo "#  Build " $@
	$(CPP) $(CPP_FLAGS) $(INCLUDE) -c $< -o $@ 

all: png++_link $(CPP_OBJS) bin_vis.o
	$(CPP) $(CPP_FLAGS) $(CPP_OBJS) bin_vis.o $(LINK_FLAGS) -o bin_vis

png++: png++_link
	make -C ./png++

png++_link:
	touch png++ && rm png++ && ln -s -f png++-$(PNG++VER) png++

clean:
	find ./ -iname '*.o' | xargs rm
	rm ./bin_vis ./png++
