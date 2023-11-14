#include "skeleton.h"

bool Skeleton::setASF(std::string const &filename) {
	this->ASF_Filename = filename;

	char ch;
	std::fstream file;

	file.open(this->ASF_Filename);
	if (!file.is_open())
		exit(1);
	while (!file.eof()) {
		if (this->error) {
			file.close();
			return false;
		}
		skipWhiteSpace(file);

		ch = file.get();
		if (file.eof() || ch < 0)
			break;
		else if (ch == '#') {
			std::string trash;
			getline(file, trash);
			continue;
		} else if (ch == ':') {
			std::string buffer;
			file >> buffer;

			if (buffer == "version")
				file >> this->version;
			else if (buffer == "name")
				file >> this->name;
			else if (buffer == "documentation") {
				std::string str;
				getline(file, str);
				getline(file, str);
				this->documentation.append(str);
				getline(file, str);
				this->documentation.append(str);
			} else if (buffer == "units")
				this->error = !this->setUnit(file);
			else if (buffer == "root")
				this->error = !this->setRoot(file);
			else if (buffer == "bonedata")
				this->error = !this->setBoneData(file);
			else if (buffer == "hierarchy")
				this->error = !this->setHierarchy(file);
		} else {
			std::cout << "부적적한 ASF 파일" << std::endl;
			file.close();
			return false;
		}
	}
	file.close();

	return true;
}