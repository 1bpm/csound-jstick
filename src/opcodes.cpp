/*
    opcodes.cpp
    Copyright (C) 2021 Richard Knight


    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 
 */

#include <plugin.h>
#include "linux/joystick.h"
#include "joystick.hpp"

struct jstick : csnd::Plugin<2, 1> {
    static constexpr char const *otypes = "k[]k[]";
    static constexpr char const *itypes = "i";
	Joystick js;
	MYFLT* saxis;
	MYFLT* sbuttons;

    int init() {
		csound->plugin_deinit(this);
		csnd::Vector<MYFLT> &axis = outargs.vector_data<MYFLT>(0);
		csnd::Vector<MYFLT> &buttons = outargs.vector_data<MYFLT>(1);

		saxis = (MYFLT*) csound->calloc(4*sizeof(MYFLT));
		sbuttons = (MYFLT*) csound->calloc(12*sizeof(MYFLT));

		axis.init(csound, 4);
		buttons.init(csound, 12);
		js.init((int)inargs[0]);
		if (!js.isFound()) {
			return csound->init_error("cannot open joypad");
		}
        return OK;
    }


	int deinit() {
		delete js;
		return OK;
	}
    
    int kperf() {
		csnd::Vector<MYFLT> &axis = outargs.vector_data<MYFLT>(0);
		csnd::Vector<MYFLT> &buttons = outargs.vector_data<MYFLT>(1);
		axis.init(csound, 4);
		buttons.init(csound, 12);
		JoystickEvent event;
		bool isAxis;
		int type;
		MYFLT val;
		while (js.sample(&event)) {
			isAxis = event.isAxis();
			type = event.number;
			val = event.value;
		}
		if (isAxis) {
			saxis[type] = FL(((32767.0)+val)/65534);
		} else {
			sbuttons[type] = val;
		}
		memcpy(axis.data_array(), saxis, sizeof(MYFLT)*4);
		memcpy(buttons.data_array(), sbuttons, sizeof(MYFLT)*12);

        return OK;
    }
};


#include <modload.h>

void csnd::on_load(csnd::Csound *csound) {
    csnd::plugin<jstick>(csound, "jstick", csnd::thread::ik);
}
