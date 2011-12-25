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


CPP := g++
CPP_FLAGS := -g

INCLUDE := -L/usr/local/include `libpng-config --cflags`
LINK_FLAGS := -L/usr/local/lib `libpng-config --ldflags`

%.o: %.cpp
	@echo "#  Build " $@
	$(CPP) $(CPP_FLAGS) $(INCLUDE) -c $< -o $@ 

all: $(CPP_OBJS) bin_vis.o
	$(CPP) $(CPP_FLAGS) $(CPP_OBJS) bin_vis.o $(LINK_FLAGS) -o bin_vis

png++:
	make -C ./png++

clean:
	find ./ -iname '*.o' | xargs rm
