#include "ploink/loader.h"
#include "ploink/window.h"

#include "third-party/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

std::vector<Level> load_levels() {
	std::vector<Level> levels;
	json j;

	std::string s(get_exe_path());
	s.append("levels.json");
	std::cout << s << "\n";

	std::ifstream file(s);
	file >> j;

	json levels_json = j["levels"];
	for (json::iterator it = levels_json.begin(); it != levels_json.end(); it++) {
		std::vector<HazardEmitter> emitters;
		std::vector<Bezier> platforms;

		json jstart = (*it)["start"];
		float s_x = jstart["x"].template get<float>();
		float s_y = jstart["y"].template get<float>();

		json jend = (*it)["end"];
		float e_x = jend["x"].template get<float>();
		float e_y = jend["y"].template get<float>();
		
		json jplatforms = (*it)["platforms"];
		for (json::iterator p = jplatforms.begin(); p != jplatforms.end(); p++) {
			json jhazard = (*p)["is_hazard"];
			json jargs = (*p)["args"];
			bool is_hazard = jhazard.is_boolean() && jhazard.template get<bool>();
			Bezier b(
				jargs.at(0).template get<float>(),
				jargs.at(1).template get<float>(),
				jargs.at(2).template get<float>(),
				jargs.at(3).template get<float>(),
				jargs.at(4).template get<float>(),
				jargs.at(5).template get<float>(),
				is_hazard);
			platforms.push_back(std::move(b));
		}

		json jenemies = (*it)["enemies"];
		if (jenemies.is_array()) {
			for (json::iterator e = jenemies.begin(); e != jenemies.end(); e++) {
				float e_x = (*e)["x"].template get<float>();
				float e_y = (*e)["y"].template get<float>();
				emitters.emplace_back(Vec{ e_x, e_y });
			}
		}

		levels.emplace_back(std::move(platforms), std::move(emitters),
			Vec{ s_x, s_y }, Vec{ e_x, e_y });
	}

	file.close();
	return levels;
}
