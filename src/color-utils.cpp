#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <cstdlib>
#include <map>

std::string xresources_path = "/.resources/.Xresources";

std::map<std::string,int> cmd;

std::map<int,std::string> color_order;

std::vector<int> rofi_order(7);

std::vector<std::string> global_xcolors(19);

int xcolors_mod = 0;

void init() {
	xresources_path = std::getenv("HOME") + xresources_path;

	cmd["l"]  = 1;
	cmd["-p"] = 2;
	cmd["gx"] = 3;
	cmd["gr"] = 4;
	cmd["gt"] = 5;
	cmd["mx"] = 6;
	cmd["mr"] = 7;
	cmd["mt"] = 8;
	cmd["-r"] = 9;
	cmd["-c"] = 10;


	color_order[0] = "black dark/light";
	color_order[1] = "red dark/light";
	color_order[2] = "green dark/light";
	color_order[3] = "yellow dark/light";
	color_order[4] = "blue dark/light";
	color_order[5] = "magenta dark/light";
	color_order[6] = "cyan dark/light";
	color_order[7] = "white dark/light";

	rofi_order[0] = 16;
	rofi_order[1] = 17;
	rofi_order[2] = 16;
	rofi_order[3] = 13;
	rofi_order[4] = 7;
	rofi_order[5] = 16;
	rofi_order[6] = 13;
}


std::vector<std::string> get_xcolors_xresources() {
//void get_xcolors() {
	std::vector<std::string> xcolors(19);

	std::ifstream xresources(xresources_path);

	if(!xresources) {
		std::cout << "Cannot open file " << xresources_path << std::endl;
		exit(1);
	}

	std::string line;
	const std::regex line_regex("^\\*(color[0-9]{1,2}|background|foreground|cursorColor):.*#[0-9a-fA-F]{6}");
	const std::regex color_regex("#[0-9a-fA-F]{6}");


	while(xresources.good()) {
		std::getline(xresources,line);
		if(std::regex_match(line,line_regex)) {
			std::smatch color_match;
			std::regex_search(line,color_match,color_regex);
			//std::cout << color_match[0] << std::endl;
			int color_num = 0;
			if(std::regex_match(line, std::regex("^\\*background:.*"))) {
				color_num = 16;
			} else if(std::regex_match(line, std::regex("^\\*foreground:.*"))) {
				color_num = 17;
			} else if(std::regex_match(line, std::regex("^\\*cursorColor:.*"))) {
				color_num = 18;
			} else {
				color_num = line[6] - '0';
				if(line[7] != ':')
					color_num = color_num*10 + (line[7] - '0');
			}
			xcolors[color_num] = color_match[0];
		}
	}
	xresources.close();
	return xcolors;
}


void print_xcolors(std::vector<std::string> xcolors) {
	printf("+------ +---------+\n");
	printf("| color |  value  |\n");
	for(int i = 0; i < 19; ++i) {
		printf("|   %2d  | %s |\n",i,xcolors[i].c_str());
	}
	printf("+-------+---------+\n");
}

void gen_xresources(std::vector<std::string> xcolors, std::string path) {

	std::ofstream out(path);
	out << "*background: " << xcolors[16] << std::endl;
	out << "*foreground: " << xcolors[17] << std::endl;
	out << "*cursorColor: " << xcolors[18] << std::endl;

	for(int i = 0; i < 8; ++i) {
		out << "!! " << color_order[i] << std::endl;
		out << "*color" << i << ": " << xcolors[i] << std::endl;
		out << "*color" << i+8 << ": " << xcolors[i+8] << std::endl;
		out << std::endl;
	}
	out.close();
}

void gen_termite(std::vector<std::string> xcolors, std::string path) {

		std::ofstream out(path);
		out << "background = " << xcolors[16] << std::endl;
		out << "foreground = " << xcolors[17] << std::endl;
		out << "cursor = " << xcolors[18] << std::endl;

		for(int i = 0; i < 8; ++i) {
			out << "# " << color_order[i] << std::endl;
			out << "color" << i << " = " << xcolors[i] << std::endl;
			out << "color" << i+8 << " = " << xcolors[i+8] << std::endl;
			out << std::endl;
		}
		out.close();
}

void gen_rofi(std::vector<std::string> xcolors, std::string path) {
	std::ofstream out(path);
	out << "! State:           \'bg\',     \'fg\',     \'bgalt\',  \'hlbg\',   \'hlfg\'" << std::endl;
	out << "rofi.color-normal: " << xcolors[rofi_order[0]] << ", " << xcolors[rofi_order[1]] << ", " <<
	xcolors[rofi_order[2]] << ", " << xcolors[rofi_order[3]] << ", " << xcolors[rofi_order[4]] << std::endl;
	out << std::endl;
	out << "!                  'background', 'border'" << std::endl;
	out << "rofi.color-window: " << xcolors[rofi_order[5]] << ", " << xcolors[rofi_order[6]] << std::endl;
	out.close();
}

void merge_xresources(std::vector<std::string> xcolors, std::string path) {
	std::ifstream res(path);
	std::ofstream temp(path + ".temp");

	if(!res) {
		std::cout << "Cannot open file " << path << std::endl;
		exit(1);
	}

	std::string line;
	const std::regex line_regex("^\\*(color[0-9]{1,2}|background|foreground|cursorColor):.*#[0-9a-fA-F]{6}");


	while(res.good()) {
		std::getline(res,line);
		if(std::regex_match(line,line_regex)) {

			if(std::regex_match(line, std::regex("^\\*background:.*"))) {
				temp << "*background: " << xcolors[16] << std::endl;
			} else if(std::regex_match(line, std::regex("^\\*foreground:.*"))) {
				temp << "*foreground: " << xcolors[17] << std::endl;
			} else if(std::regex_match(line, std::regex("^\\*cursorColor:.*"))) {
				temp << "*cursorColor: " << xcolors[18] << std::endl;
			} else {
				temp << "*color";
				int color_num = line[6] - '0';
				if(line[7] != ':')
					color_num = color_num*10 + (line[7] - '0');
				temp << color_num << ": " << xcolors[color_num] << std::endl;
			}
			continue;
		}
		temp << line << std::endl;
	}


	res.close();
	temp.close();
	system( std::string("mv " + path + ".temp " + path).c_str());
}

void merge_termite(std::vector<std::string> xcolors, std::string path) {
	std::ifstream res(path);
	std::ofstream temp(path + ".temp");

	if(!res) {
		std::cout << "Cannot open file " << path << std::endl;
		exit(1);
	}

	std::string line;
	const std::regex line_regex("^(color[0-9]{1,2}|background|foreground|cursor).*=.*#[0-9a-fA-F]{6}");


	while(res.good()) {
		std::getline(res,line);
		if(std::regex_match(line,line_regex)) {

			if(std::regex_match(line, std::regex("^\\*background.*"))) {
				temp << "background = " << xcolors[16] << std::endl;
			} else if(std::regex_match(line, std::regex("^\\*foreground.*"))) {
				temp << "foreground = " << xcolors[17] << std::endl;
			} else if(std::regex_match(line, std::regex("^\\*cursorColor.*"))) {
				temp << "cursorColor = " << xcolors[18] << std::endl;
			} else {
				temp << "color";
				int color_num = line[5] - '0';
				if(line[6] >= '0' && line[6] <= 9)
					color_num = color_num*10 + (line[6] - '0');
				temp << color_num << " = " << xcolors[color_num] << std::endl;
			}
			continue;
		}
		temp << line << std::endl;
	}


	res.close();
	temp.close();
	system( std::string("mv " + path + ".temp " + path).c_str());
}

void merge_rofi(std::vector<std::string> xcolors, std::string path) {
	std::ifstream res(path);
	std::ofstream temp(path + ".temp");

	if(!res) {
		std::cout << "Cannot open file " << path << std::endl;
		exit(1);
	}

	std::string line;
	const std::regex line_regex("^rofi.color-(normal|window):");


	while(res.good()) {
		std::getline(res,line);
		if(std::regex_match(line,line_regex)) {
			if(std::regex_match(line, std::regex("^rofi.color-normal:.*"))) {
				temp << "rofi.color-normal: " << xcolors[rofi_order[0]] << ", " << xcolors[rofi_order[1]] << ", " <<
				xcolors[rofi_order[2]] << ", " << xcolors[rofi_order[3]] << ", " << xcolors[rofi_order[4]] << std::endl;
			} else {
				temp << "rofi.color-window: " << xcolors[rofi_order[5]] << ", " << xcolors[rofi_order[6]] << std::endl;
			}
			continue;
		}
		temp << line << std::endl;
	}


	res.close();
	temp.close();
	system( std::string("mv " + path + ".temp " + path).c_str());
}


std::vector<std::string> get_xcolors() {
	switch (xcolors_mod) {
		case 0:
			return get_xcolors_xresources();
		break;
		case 1:
			return global_xcolors;
		break;
		default:
			return get_xcolors_xresources();
	}
}


int main(int argc, char *argv[]) {
	init();
	if(argc < 2) {
		printf("Please specify the command\n");
		return 0;
	}
	for(int i = 1; i < argc; ++i) {
		switch (cmd[argv[i]]) {
			case 1:
				print_xcolors(get_xcolors());
			break;
			case 2:
				i++;
				xresources_path = argv[i];
			break;
			case 3:
				i++;
				gen_xresources(get_xcolors(),argv[i]);
			break;
			case 4:
				i++;
				gen_rofi(get_xcolors(),argv[i]);
			break;
			case 5:
				i++;
				gen_termite(get_xcolors(),argv[i]);
			break;
			case 6:
				i++;
				merge_xresources(get_xcolors(),argv[i]);
			break;
			case 7:
				i++;
				merge_rofi(get_xcolors(),argv[i]);
			break;
			case 8:
				i++;
				merge_termite(get_xcolors(),argv[i]);
			break;
			case 9:
				if(argc - i < 7) {
					printf("Need 7 numbers for rofi setup");
					exit(1);
				}
				for(int q = 0; q < 7; ++q) {
						rofi_order[q] = std::stoi(argv[i+q+1]);
				}
				i += 7;
			break;
			case 10:
				xcolors_mod = 1;
				if(argc - i < 19) {
					printf("Need 19 numbers for colors setup");
					exit(1);
				}
				for(int q = 0; q < 19; ++q) {
					global_xcolors[q] = argv[i+q+1];
				}
				i+=19;
			break;
			default:
				printf("%s: Command not found\n",argv[i]);
		}
	}
	return 0;
}
