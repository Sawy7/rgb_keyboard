/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

//writer functions (apply changes to keyboard)

int rgb_keyboard::keyboard::write_brightness(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	
	if( _profile == 1 ){
		data_settings[1] = 0x08 + _brightness;
		data_settings[8] = _brightness;
		data_settings[5] = 0x01;
	} else if( _profile == 2 ){
		data_settings[1] = 0x32 + _brightness;
		data_settings[8] = _brightness;
		data_settings[5] = 0x2b;
	} else if( _profile == 3 ){
		data_settings[1] = 0x5c + _brightness;
		data_settings[8] = _brightness;
		data_settings[5] = 0x55;
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write brightness data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_speed(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	
	if( _profile == 1 ){
		data_settings[1] = 0x0d - _speed;
		data_settings[8] = 0x04 - _speed;
		data_settings[5] = 0x02;
	} else if( _profile == 2 ){
		data_settings[1] = 0x37 - _speed;
		data_settings[8] = 0x04 - _speed;
		data_settings[5] = 0x2c;
	} else if( _profile == 3 ){
		data_settings[1] = 0x61 - _speed;
		data_settings[8] = 0x04 - _speed;
		data_settings[5] = 0x56;
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
		
	return res;
}

int rgb_keyboard::keyboard::write_direction(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	
	if( _profile == 1 ){
		switch( _direction ){
			case d_left:
				data_settings[1] = 0x09;
				data_settings[2] = 0x01;
				data_settings[5] = 0x03;
				data_settings[8] = 0xff;
				break;
			case d_right:
				data_settings[1] = 0x0a;
				data_settings[2] = 0x00;
				data_settings[5] = 0x03;
				data_settings[8] = 0x00;
			default:
				break;
		}
	} else if( _profile == 2 ){
		switch( _direction ){
			case d_left:
				data_settings[1] = 0x33;
				data_settings[2] = 0x01;
				data_settings[5] = 0x2d;
				data_settings[8] = 0xff;
				break;
			case d_right:
				data_settings[1] = 0x34;
				data_settings[2] = 0x00;
				data_settings[5] = 0x2d;
				data_settings[8] = 0x00;
			default:
				break;
		}
	} else if( _profile == 3 ){
		switch( _direction ){
			case d_left:
				data_settings[1] = 0x5d;
				data_settings[2] = 0x01;
				data_settings[5] = 0x57;
				data_settings[8] = 0xff;
				break;
			case d_right:
				data_settings[1] = 0x5e;
				data_settings[2] = 0x00;
				data_settings[5] = 0x57;
				data_settings[8] = 0x00;
			default:
				break;
		}
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
		
	return res;
}

int rgb_keyboard::keyboard::write_mode(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	
	if( _profile == 1 ){
		switch( _mode ){
			case m_horizontal_wave://ok
				data_settings[1] = 0x08;
				data_settings[8] = 0x01;
				break;
			case m_pulse://ok
				data_settings[1] = 0x09;
				data_settings[8] = 0x02;
				break;
			case m_hurricane://ok
				data_settings[1] = 0x0a;
				data_settings[8] = 0x03;
				break;
			case m_breathing_color://ok
				data_settings[1] = 0x0b;
				data_settings[8] = 0x04;
				break;
			case m_breathing://ok
				data_settings[1] = 0x0c;
				data_settings[8] = 0x05;
				break;
			case m_fixed://ok
				data_settings[1] = 0x0d;
				data_settings[8] = 0x06;
				break;
			case m_reactive_single://ok
				data_settings[1] = 0x0e;
				data_settings[8] = 0x07;
				break;
			case m_reactive_ripple://ok
				data_settings[1] = 0x0f;
				data_settings[8] = 0x08;
				break;
			case m_reactive_horizontal://ok
				data_settings[1] = 0x10;
				data_settings[8] = 0x09;
				break;
			case m_waterfall://ok
				data_settings[1] = 0x11;
				data_settings[8] = 0x0a;
				break;
			case m_swirl://ok
				data_settings[1] = 0x12;
				data_settings[8] = 0x0b;
				break;
			case m_vertical_wave://ok
				data_settings[1] = 0x13;
				data_settings[8] = 0x0c;
				break;
			case m_sine://ok
				data_settings[1] = 0x14;
				data_settings[8] = 0x0d;
				break;
			case m_vortex://ok
				data_settings[1] = 0x15;
				data_settings[8] = 0x0e;
				break;
			case m_rain://ok
				data_settings[1] = 0x16;
				data_settings[8] = 0x0f;
				break;
			case m_diagonal_wave://ok
				data_settings[1] = 0x17;
				data_settings[8] = 0x10;
				break;
			case m_reactive_color://ok
				data_settings[1] = 0x18;
				data_settings[8] = 0x11;
				break;
			case m_ripple://ok
				data_settings[1] = 0x19;
				data_settings[8] = 0x12;
				break;
			case m_custom://ok
				data_settings[1] = 0x1b;
				data_settings[8] = 0x14;
				break;
			case m_off://ok
				data_settings[1] = 0x1a;
				data_settings[8] = 0x13;
				break;
			default:
				break;
		}
	} else if( _profile == 2 ){
		switch( _mode ){
			case m_horizontal_wave://ok
				data_settings[1] = 0x32;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x01;
				break;
			case m_pulse://ok
				data_settings[1] = 0x33;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x02;
				break;
			case m_hurricane://ok
				data_settings[1] = 0x34;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x03;
				break;
			case m_breathing_color://ok
				data_settings[1] = 0x35;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x04;
				break;
			case m_breathing://ok
				data_settings[1] = 0x36;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x05;
				break;
			case m_fixed://ok ---
				data_settings[1] = 0x37;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x06;
				break;
			case m_reactive_single://ok
				data_settings[1] = 0x38;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x07;
				break;
			case m_reactive_ripple://ok
				data_settings[1] = 0x39;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x08;
				break;
			case m_reactive_horizontal://ok
				data_settings[1] = 0x3a;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x09;
				break;
			case m_waterfall://ok
				data_settings[1] = 0x3b;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0a;
				break;
			case m_swirl://ok
				data_settings[1] = 0x3c;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0b;
				break;
			case m_vertical_wave://ok
				data_settings[1] = 0x3d;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0c;
				break;
			case m_sine://ok
				data_settings[1] = 0x3e;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0d;
				break;
			case m_vortex://ok
				data_settings[1] = 0x3f;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0e;
				break;
			case m_rain://ok
				data_settings[1] = 0x40;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0f;
				break;
			case m_diagonal_wave://ok
				data_settings[1] = 0x41;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x10;
				break;
			case m_reactive_color://ok
				data_settings[1] = 0x42;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x11;
				break;
			case m_ripple://ok
				data_settings[1] = 0x43;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x12;
				break;
			case m_custom://ok
				data_settings[1] = 0x45;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x14;
				break;
			case m_off://ok
				data_settings[1] = 0x44;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x13;
				break;
			default:
				break;
		}
	} else if( _profile == 3 ){
		switch( _mode ){
			case m_horizontal_wave://ok
				data_settings[1] = 0x5c;
				data_settings[5] = 0x54;
				data_settings[8] = 0x01;
				break;
			case m_pulse://ok
				data_settings[1] = 0x5d;
				data_settings[5] = 0x54;
				data_settings[8] = 0x02;
				break;
			case m_hurricane://ok
				data_settings[1] = 0x5e;
				data_settings[5] = 0x54;
				data_settings[8] = 0x03;
				break;
			case m_breathing_color://ok
				data_settings[1] = 0x5f;
				data_settings[5] = 0x54;
				data_settings[8] = 0x04;
				break;
			case m_breathing://ok
				data_settings[1] = 0x60;
				data_settings[5] = 0x54;
				data_settings[8] = 0x05;
				break;
			case m_fixed://ok ---
				data_settings[1] = 0x61;
				data_settings[5] = 0x54;
				data_settings[8] = 0x06;
				break;
			case m_reactive_single://ok
				data_settings[1] = 0x62;
				data_settings[5] = 0x54;
				data_settings[8] = 0x07;
				break;
			case m_reactive_ripple://ok
				data_settings[1] = 0x63;
				data_settings[5] = 0x54;
				data_settings[8] = 0x08;
				break;
			case m_reactive_horizontal://ok
				data_settings[1] = 0x64;
				data_settings[5] = 0x54;
				data_settings[8] = 0x09;
				break;
			case m_waterfall://ok
				data_settings[1] = 0x65;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0a;
				break;
			case m_swirl://ok
				data_settings[1] = 0x66;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0b;
				break;
			case m_vertical_wave://ok
				data_settings[1] = 0x67;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0c;
				break;
			case m_sine://ok
				data_settings[1] = 0x68;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0d;
				break;
			case m_vortex://ok
				data_settings[1] = 0x69;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0e;
				break;
			case m_rain://ok
				data_settings[1] = 0x6a;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0f;
				break;
			case m_diagonal_wave://ok
				data_settings[1] = 0x6b;
				data_settings[5] = 0x54;
				data_settings[8] = 0x10;
				break;
			case m_reactive_color://ok
				data_settings[1] = 0x6c;
				data_settings[5] = 0x54;
				data_settings[8] = 0x11;
				break;
			case m_ripple://ok
				data_settings[1] = 0x6d;
				data_settings[5] = 0x54;
				data_settings[8] = 0x12;
				break;
			case m_custom://ok
				data_settings[1] = 0x6f;
				data_settings[5] = 0x54;
				data_settings[8] = 0x14;
				break;
			case m_off://ok
				data_settings[1] = 0x6e;
				data_settings[5] = 0x54;
				data_settings[8] = 0x13;
				break;
			default:
				break;
		}
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_color(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings_1[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings_1));
	uint8_t data_settings_2[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings_2));
	
	if( _profile == 1 ){
		data_settings_1[1] = 0x0b;
		data_settings_1[5] = 0x04;
		if( _rainbow ){
			data_settings_1[1] = 0x0c;
			data_settings_1[8] = 0x01;
		}
		
		data_settings_2[2] = 0x02;
		data_settings_2[4] = 0x03;
		data_settings_2[5] = 0x05;
		data_settings_2[8] = _color_r;
		data_settings_2[9] = _color_g;
		data_settings_2[10] = _color_b;
	} else if( _profile == 2 ){
		data_settings_1[1] = 0x35;
		data_settings_1[5] = 0x2e;
		if( _rainbow ){
			data_settings_1[1] = 0x36;
			data_settings_1[5] = 0x2e;
			data_settings_1[8] = 0x01;
		}
		
		data_settings_2[4] = 0x03;
		data_settings_2[5] = 0x2f;
		data_settings_2[8] = _color_r;
		data_settings_2[9] = _color_g;
		data_settings_2[10] = _color_b;
	} else if( _profile == 3 ){
		data_settings_1[1] = 0x5f;
		data_settings_1[5] = 0x58;
		if( _rainbow ){
			data_settings_1[1] = 0x60;
			data_settings_1[5] = 0x58;
			data_settings_1[8] = 0x01;
		}
		
		data_settings_2[4] = 0x03;
		data_settings_2[5] = 0x59;
		data_settings_2[8] = _color_r;
		data_settings_2[9] = _color_g;
		data_settings_2[10] = _color_b;
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings_1, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings_2, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
		
	return res;
}

//writes custom pattern to keyboard
int rgb_keyboard::keyboard::write_custom(){
	
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[2] = 0x02;
	data_settings[3] = 0x11;
	data_settings[4] = 0x03;
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//process loaded config and send data
	for( std::pair< std::string, std::array<uint8_t, 3> > element : _key_colors ){
		if( _keycodes.find( element.first ) != _keycodes.end() ){
			//if keycode is stored in _keycodes: set values in data packets
			
			//prepare data packet
			if( _profile == 2 ){
				/*data_settings[3] = 0x11;
				data_settings[4] = 0x03;
				
				//keycode: different to _profile == 1
				data_settings[1] = _keycodes.at(element.first)[0];
				data_settings[5] = _keycodes.at(element.first)[1];
				data_settings[6] = _keycodes.at(element.first)[2];
				
				//color
				data_settings[8] = element.second[0];
				data_settings[9] = element.second[1];
				data_settings[10] = element.second[2];*/
				throw std::invalid_argument("Currently not available with compatibility mode 2");
			} else{
				//keycode
				data_settings[1] = _keycodes.at(element.first)[0];
				data_settings[5] = _keycodes.at(element.first)[1];
				data_settings[6] = _keycodes.at(element.first)[2];
				
				//color
				data_settings[8] = element.second[0];
				data_settings[9] = element.second[1];
				data_settings[10] = element.second[2];
			}
			
			//send data
			//write first data packet to endpoint 3
			res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
			64, &transferred, 1000);
			
			//read from endpoint 2
			res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
			&transferred, 1000);
		}
	}
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_variant(){
	
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[5] = 0x08;
	
	//convert variant	
	if( _profile == 1 ){
		if( _variant == v_color_red ){
			data_settings[1] = 0x0f;
			data_settings[8] = 0x00;
		} else if( _variant == v_color_yellow ){
			data_settings[1] = 0x10;
			data_settings[8] = 0x01;
		} else if( _variant == v_color_green ){
			data_settings[1] = 0x11;
			data_settings[8] = 0x02;
		} else if( _variant == v_color_blue ){
			data_settings[1] = 0x12;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else if( _profile == 2 ){
		if( _variant == v_color_red ){
			data_settings[1] = 0x39;
			data_settings[5] = 0x32;
			data_settings[8] = 0x00;
		} else if( _variant == v_color_yellow ){
			data_settings[1] = 0x3a;
			data_settings[5] = 0x32;
			data_settings[8] = 0x01;
		} else if( _variant == v_color_green ){
			data_settings[1] = 0x3b;
			data_settings[5] = 0x32;
			data_settings[8] = 0x02;
		} else if( _variant == v_color_blue ){
			data_settings[1] = 0x3c;
			data_settings[5] = 0x32;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else if( _profile == 3 ){
		if( _variant == v_color_red ){
			data_settings[1] = 0x63;
			data_settings[5] = 0x5c;
			data_settings[8] = 0x00;
		} else if( _variant == v_color_yellow ){
			data_settings[1] = 0x64;
			data_settings[5] = 0x5c;
			data_settings[8] = 0x01;
		} else if( _variant == v_color_green ){
			data_settings[1] = 0x65;
			data_settings[5] = 0x5c;
			data_settings[8] = 0x02;
		} else if( _variant == v_color_blue ){
			data_settings[1] = 0x66;
			data_settings[5] = 0x5c;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_report_rate(){
	
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[5] = 0x0f;
	
	//convert report rate	
	if( _profile == 1 ){
		if( _report_rate == r_125Hz ){
			data_settings[1] = 0x16;
			data_settings[8] = 0x00;
		} else if( _report_rate == r_250Hz ){
			data_settings[1] = 0x17;
			data_settings[8] = 0x01;
		} else if( _report_rate == r_500Hz ){
			data_settings[1] = 0x18;
			data_settings[8] = 0x02;
		} else if( _report_rate == r_1000Hz ){
			data_settings[1] = 0x19;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else if( _profile == 2 ){
		if( _report_rate == r_125Hz ){
			data_settings[1] = 0x40;
			data_settings[5] = 0x39;
			data_settings[8] = 0x00;
		} else if( _report_rate == r_250Hz ){
			data_settings[1] = 0x41;
			data_settings[5] = 0x39;
			data_settings[8] = 0x01;
		} else if( _report_rate == r_500Hz ){
			data_settings[1] = 0x42;
			data_settings[5] = 0x39;
			data_settings[8] = 0x02;
		} else if( _report_rate == r_1000Hz ){
			data_settings[1] = 0x43;
			data_settings[5] = 0x39;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else if( _profile == 3 ){
		if( _report_rate == r_125Hz ){
			data_settings[1] = 0x6a;
			data_settings[5] = 0x63;
			data_settings[8] = 0x00;
		} else if( _report_rate == r_250Hz ){
			data_settings[1] = 0x6b;
			data_settings[5] = 0x63;
			data_settings[8] = 0x01;
		} else if( _report_rate == r_500Hz ){
			data_settings[1] = 0x6c;
			data_settings[5] = 0x63;
			data_settings[8] = 0x02;
		} else if( _report_rate == r_1000Hz ){
			data_settings[1] = 0x6d;
			data_settings[5] = 0x63;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_key_mapping(){
	
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packets
	uint8_t data_remap[8][64];
	std::copy(std::begin(_data_remap_1), std::end(_data_remap_1), std::begin(data_remap[0]));
	std::copy(std::begin(_data_remap_2), std::end(_data_remap_2), std::begin(data_remap[1]));
	std::copy(std::begin(_data_remap_3), std::end(_data_remap_3), std::begin(data_remap[2]));
	std::copy(std::begin(_data_remap_4), std::end(_data_remap_4), std::begin(data_remap[3]));
	std::copy(std::begin(_data_remap_5), std::end(_data_remap_5), std::begin(data_remap[4]));
	std::copy(std::begin(_data_remap_6), std::end(_data_remap_6), std::begin(data_remap[5]));
	std::copy(std::begin(_data_remap_7), std::end(_data_remap_7), std::begin(data_remap[6]));
	std::copy(std::begin(_data_remap_8), std::end(_data_remap_8), std::begin(data_remap[7]));
	
	if( _profile == 2 ){
		/*for( std::pair< std::string, std::string > element : _keymap ){
			if( _keymap_offsets.find( element.first ) != _keymap_offsets.end() &&
				_keymap_options.find( element.second ) != _keymap_options.end() ){
				data_remap[ _keymap_offsets[element.first][0][0] ][ _keymap_offsets[element.first][0][1] ]
				= _keymap_options[ element.second ][0];
				data_remap[ _keymap_offsets[element.first][1][0] ][ _keymap_offsets[element.first][1][1] ]
				= _keymap_options[ element.second ][1];
				data_remap[ _keymap_offsets[element.first][2][0] ][ _keymap_offsets[element.first][2][1] ]
				= _keymap_options[ element.second ][2];
			}
		}*/
		throw std::invalid_argument("Currently not available with compatibility mode 2");
	} else{
		for( std::pair< std::string, std::string > element : _keymap ){
			if( _keymap_offsets.find( element.first ) != _keymap_offsets.end() &&
				_keymap_options.find( element.second ) != _keymap_options.end() ){
				data_remap[ _keymap_offsets[element.first][0][0] ][ _keymap_offsets[element.first][0][1] ]
				= _keymap_options[ element.second ][0];
				data_remap[ _keymap_offsets[element.first][1][0] ][ _keymap_offsets[element.first][1][1] ]
				= _keymap_options[ element.second ][1];
				data_remap[ _keymap_offsets[element.first][2][0] ][ _keymap_offsets[element.first][2][1] ]
				= _keymap_options[ element.second ][2];
			}
		}
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write macro data here
	
	//write keymap data
	for( int i = 0; i < 8; i++ ){
		//write data packet to endpoint 3
		res += libusb_interrupt_transfer( _handle, 0x03, data_remap[i], 
		64, &transferred, 1000);
		//read from endpoint 2
		res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
		&transferred, 1000);
	}
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_active_profile(){
	
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packets
	uint8_t data_remap[17][64];
	std::copy(std::begin(_data_profile_1), std::end(_data_profile_1), std::begin(data_remap[0]));
	std::copy(std::begin(_data_profile_2), std::end(_data_profile_2), std::begin(data_remap[1]));
	std::copy(std::begin(_data_profile_3), std::end(_data_profile_3), std::begin(data_remap[2]));
	std::copy(std::begin(_data_profile_4), std::end(_data_profile_4), std::begin(data_remap[3]));
	std::copy(std::begin(_data_profile_5), std::end(_data_profile_5), std::begin(data_remap[4]));
	std::copy(std::begin(_data_profile_6), std::end(_data_profile_6), std::begin(data_remap[5]));
	std::copy(std::begin(_data_profile_7), std::end(_data_profile_7), std::begin(data_remap[6]));
	std::copy(std::begin(_data_profile_8), std::end(_data_profile_8), std::begin(data_remap[7]));
	std::copy(std::begin(_data_profile_9), std::end(_data_profile_9), std::begin(data_remap[8]));
	std::copy(std::begin(_data_profile_10), std::end(_data_profile_10), std::begin(data_remap[9]));
	std::copy(std::begin(_data_profile_11), std::end(_data_profile_11), std::begin(data_remap[10]));
	std::copy(std::begin(_data_profile_12), std::end(_data_profile_12), std::begin(data_remap[11]));
	std::copy(std::begin(_data_profile_13), std::end(_data_profile_13), std::begin(data_remap[12]));
	std::copy(std::begin(_data_profile_14), std::end(_data_profile_14), std::begin(data_remap[13]));
	std::copy(std::begin(_data_profile_15), std::end(_data_profile_15), std::begin(data_remap[14]));
	std::copy(std::begin(_data_profile_16), std::end(_data_profile_16), std::begin(data_remap[15]));
	std::copy(std::begin(_data_profile_17), std::end(_data_profile_17), std::begin(data_remap[16]));
	
	// change data
	if( _active_profile == 1 ){
		
		// 1 is default, do nothing
		
	} else if( _active_profile == 2 ){
		
		data_remap[7][1] = 0x49;
		data_remap[7][6] = 0x02;
		data_remap[8][1] = 0x75;
		data_remap[8][6] = 0x02;
		data_remap[9][1] = 0xb2;
		data_remap[9][6] = 0x02;
		data_remap[10][1] = 0xe9;
		data_remap[10][6] = 0x02;
		data_remap[11][1] = 0x21;
		data_remap[11][6] = 0x02;
		data_remap[12][1] = 0x58;
		data_remap[12][6] = 0x03;
		data_remap[13][1] = 0x8e;
		data_remap[13][6] = 0x03;
		data_remap[16][1] = 0xe1;
		data_remap[16][18] = 0x01;
		
	} else if( _active_profile == 3 ){
		
		data_remap[7][1] = 0x4b;
		data_remap[7][6] = 0x04;
		data_remap[8][1] = 0x77;
		data_remap[8][6] = 0x04;
		data_remap[9][1] = 0xb4;
		data_remap[9][6] = 0x04;
		data_remap[10][1] = 0xeb;
		data_remap[10][6] = 0x04;
		data_remap[11][1] = 0x23;
		data_remap[11][6] = 0x04;
		data_remap[12][1] = 0x5a;
		data_remap[12][6] = 0x05;
		data_remap[13][1] = 0x90;
		data_remap[13][6] = 0x05;
		data_remap[16][1] = 0xe2;
		data_remap[16][18] = 0x02;
		
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	for( int i = 0; i < 17; i++ ){
		//write data packet to endpoint 3
		res += libusb_interrupt_transfer( _handle, 0x03, data_remap[i], 
		64, &transferred, 1000);
		//read from endpoint 2
		res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
		&transferred, 1000);
	}
	
	return res;
}
