#include "skeleton.h"

static glm::mat4 eulerRotation  (float x, float y, float z, int order) {
	glm::mat4 X = glm::rotate(glm::mat4(1), x, glm::vec3(1, 0, 0));
	glm::mat4 Y = glm::rotate(glm::mat4(1), y, glm::vec3(0, 1, 0));
	glm::mat4 Z = glm::rotate(glm::mat4(1), z, glm::vec3(0, 0, 1));

	if (order == EULER_XYZ)
		return Z * Y * X;
	else if (order == EULER_XZY)
		return Y * Z * X;
	else if (order == EULER_YXZ)
		return Z * X * Y;
	else if (order == EULER_YZX)
		return X * Z * Y;
	else if (order == EULER_ZXY)
		return Y * X * Z;
	else if (order == EULER_ZYX)
		return X * Y * Z;

	return Z * Y * X;
}

static void skipWhiteSpace(std::fstream &file) {
  while (1) {
    char c = file.peek();
    if (std::isspace(c))
      file.get();
    else
      break;
  }
}

static std::string trim(std::string &str) {
  std::string res;

  for (std::string::iterator it = str.begin(); it != str.end(); it++) {
    if (*it == '(' || *it == ')')
      continue;
    res.push_back(*it);
  }
  return res;
}

static std::string peekLine(std::fstream &file) {
  std::string str;

  getline(file, str);
  file.seekg(str.length() * -1, std::ios_base::seekdir::cur);
  return str;
}

static std::string peekWord(std::fstream &file) {
  std::string str;

  file >> str;
  file.seekg(str.length() * -1, std::ios_base::seekdir::cur);
  return str;
}

bool Skeleton::setASF(std::string const &filename) {
  char ch;
  std::fstream file;

  file.open(filename);
  if (!file.is_open())
    std::exit(1);
  while (!file.eof()) {
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
      } else if (buffer == "units") {
        if (!this->setUnit(file))
          return false;
      } else if (buffer == "root") {
        if (!this->setRoot(file))
          return false;
      } else if (buffer == "bonedata") {
        if (!this->setBoneData(file))
          return false;
      } else if (buffer == "hierarchy") {
        if (!this->setHierarchy(file))
          return false;
      }
    } else {
      std::cout << "부적적한 ASF 파일" << std::endl;
      file.close();
      return false;
    }
  }
  file.close();

  return true;
}

bool Skeleton::setUnit(std::fstream &file) {
  std::string buffer;
  bool check[3] = {false, false, false};

  for (int i = 0; i < 3; i++) {
    file >> buffer;
    if (buffer == "mass") {
      check[0] = true;
      file >> this->mass_;
    } else if (buffer == "length") {
      check[1] = true;
      file >> this->globalLengthMultiplier_;
    } else if (buffer == "angle") {
      check[2] = true;
      file >> buffer;
      if (buffer == "deg") {
        this->isDegree_ = true;
        this->AMCisRad = false;
      } else if (buffer == "rad") {
        this->isDegree_ = false;
        this->AMCisRad = true;
      } else
        return false;
    } else
      return false;
  }

  for (int i = 0; i < 3; i++) {
    if (!check[i])
      return false;
  }
  return true;
}

bool Skeleton::setRoot(std::fstream &file) {
  Joint root;

  root.index = 0;
  root.name = "root";

  std::string buffer;
  bool check[4] = {false, false, false, false};

  for (int i = 0; i < 4; i++) {
    file >> buffer;
    if (buffer == "axis") {
      check[0] = true;
      file >> buffer;

      for (int i = 0; i < 3; i++)
        buffer[i] = ::toupper(buffer[i]);

      if (buffer == "XYZ")
        root.eulerOrder = EULER_XYZ;
      else if (buffer == "XZY")
        root.eulerOrder = EULER_XZY;
      else if (buffer == "YXZ")
        root.eulerOrder = EULER_YXZ;
      else if (buffer == "YZX")
        root.eulerOrder = EULER_YZX;
      else if (buffer == "ZXY")
        root.eulerOrder = EULER_ZXY;
      else if (buffer == "ZYX")
        root.eulerOrder = EULER_ZYX;
      else
        return false;

    } else if (buffer == "order") {
      check[1] = true;
      if (!this->setRootOrder(file, root))
        return false;
    } else if (buffer == "position") {
      check[2] = true;
      for (int i = 0; i < 3; i++)
        file >> root.position[i];
    } else if (buffer == "orientation") {
      check[3] = true;
      for (int i = 0; i < 3; i++)
        file >> root.axis[i];
      if (this->isDegree_ == true) {
        for (int i = 0; i < 3; i++)
          root.axis[i] = glm::radians(root.axis[i]);
      }
    } else
      return false;
  }
  glm::mat4 c =
      eulerRotation(root.axis[0], root.axis[1], root.axis[2], root.eulerOrder);
  root._C = c;
  root._Cinv = glm::inverse(c);

  for (int i = 0; i < 4; i++) {
    if (!check[i])
      return false;
  }
  this->joints.insert(std::make_pair("root", root));
  return true;
}

bool Skeleton::setRootOrder(std::fstream &file, Joint &root) {
  std::string buffer;

  for (int i = 0; i < 6; i++) {
    file >> buffer;

    std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    if (buffer != "tx" && buffer != "ty" && buffer != "tz" && buffer != "rx" &&
        buffer != "ry" && buffer != "rz")
      return false;
    root.dof.push_back(buffer);
  }
  return true;
}

bool Skeleton::setBoneData(std::fstream &file) {
  std::string buffer;

  glm::vec3 direction;
  float length;

  while (1) {
    if (file.eof() || file.peek() == ':')
      return true;

    file >> buffer;
    if (buffer != "begin")
      return false;

    Joint joint;
    std::string euler;
    while (1) {
      file >> buffer;
      if (buffer == "id")
        file >> joint.index;
      else if (buffer == "name")
        file >> joint.name;
      else if (buffer == "direction") {
        float value;
        for (int i = 0; i < 3; i++) {
          file >> value;
          direction[i] = value;
        }
        direction = glm::normalize(direction);
      } else if (buffer == "length")
        file >> length;
      else if (buffer == "axis") {
        float value;
        for (int i = 0; i < 3; i++) {
          file >> value;
          joint.axis[i] = value;
        }
        if (this->isDegree_ == true) {
          for (int i = 0; i < 3; i++)
            joint.axis[i] = glm::radians(joint.axis[i]);
        }
        file >> buffer;
        for (int i = 0; i < 3; i++)
          buffer[i] = ::toupper(buffer[i]);

        if (buffer == "XYZ")
          joint.eulerOrder = EULER_XYZ;
        else if (buffer == "XZY")
          joint.eulerOrder = EULER_XZY;
        else if (buffer == "YXZ")
          joint.eulerOrder = EULER_YXZ;
        else if (buffer == "YZX")
          joint.eulerOrder = EULER_YZX;
        else if (buffer == "ZXY")
          joint.eulerOrder = EULER_ZXY;
        else if (buffer == "ZYX")
          joint.eulerOrder = EULER_ZYX;

      } else if (buffer == "dof") {
        if (!this->setBoneDataDof(file, joint))
          return false;
      } else if (buffer == "limits") {
        if (!this->setBoneDataLimits(file, joint))
          return false;
      } else if (buffer == "end") {
        glm::mat4 c = eulerRotation(joint.axis[0], joint.axis[1], joint.axis[2],
                                    joint.eulerOrder);
        joint._C = c;
        joint._Cinv = glm::inverse(c);
        joint.position = this->globalLengthMultiplier_ * length * direction;

        // joint._ROT = joint._C * joint._Cinv;
        // joint._B = joint.position;

        this->joints.insert(std::pair<std::string, Joint>(joint.name, joint));
        getline(file, buffer);
        break;
      } else
        return false;
    }
  }

  return true;
}

bool Skeleton::setBoneDataDof(std::fstream &file, Joint &joint) {
  std::string line;
  std::string buffer;

  getline(file, line);

  std::stringstream ss(line);
  while (1) {
    ss >> buffer;
    if (ss.eof())
      break;

    std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    if (buffer != "rx" && buffer != "ry" && buffer != "rz")
      return false;
    joint.dof.push_back(buffer);
  }
  return true;
}

bool Skeleton::setBoneDataLimits(std::fstream &file, Joint &joint) {
  std::string line;
  std::string buffer;
  float floatBuffer;

  while (1) {
    buffer = peekWord(file);
    if (buffer == "end") {
      if (joint.limits.size() % 2)
        return false;
      else
        return true;
    }
    getline(file, buffer);
    std::stringstream ss(trim(buffer));
    glm::vec2 lim;
    ss >> floatBuffer;
    if (this->isDegree_ == true)
      floatBuffer = glm::radians(floatBuffer);
    lim.x = floatBuffer;
    ss >> floatBuffer;
    if (this->isDegree_ == true)
      floatBuffer = glm::radians(floatBuffer);
    lim.y = floatBuffer;
    joint.limits.push_back(lim);
  }
}

bool Skeleton::setHierarchy(std::fstream &file) {
  std::string buffer;

  if (file.eof() || file.peek() == ':')
    return true;

  file >> buffer;
  if (buffer != "begin")
    return false;
  getline(file, buffer);

  while (1) {
    file >> buffer;
    if (buffer == "end")
      return true;
    std::string line;
    getline(file, line);

    std::stringstream ss(line);
    std::string parent = buffer;
    std::vector<std::string> childs;
    while (1) {
      ss >> buffer;
      if (ss.eof())
        break;
      childs.push_back(buffer);
    }
    this->hierarchy.insert(std::make_pair(parent, childs));
  }
  return true;
  ;
}

bool Skeleton::setAMC(std::string const &filename) {
  this->AMC_Filename = filename;

  char ch;
  std::fstream file;

  file.open(this->AMC_Filename);
  if (!file.is_open())
    exit(1);
  while (!file.eof()) {
    skipWhiteSpace(file);

    ch = file.peek();
    if (file.eof() || ch < 0)
      break;
    else if (ch == '#') {
      std::string trash;
      getline(file, trash);
      continue;
    } else if (ch == ':') {
      std::string buffer;
      file >> buffer;

      if (buffer == "FULLY-SPECIFIED")
        this->isSpecified = true;
      else if (buffer == "DEGREES")
        this->AMCisRad = false;
      else if (buffer == "RADIANS")
        this->AMCisRad = true;

      getline(file, buffer);
    } else if (isdigit(ch)) {
      KeyFrame frame;

      file >> frame.sequence;
      if (this->keyFrame.size() + 1 != frame.sequence) {
        std::exit(-1);
      }
      frame.time = frame.sequence / FRAMERATE;
      this->keyFrame.push_back(frame);
    } else {
      std::string jointName;
      std::vector<float> motion;
      float buffer;
      std::string line;

      getline(file, line);
      std::stringstream ss(line);

      ss >> jointName;
      int rootIdx = 0;
      while (!ss.eof()) {
        ss >> buffer;
        // if (this->AMCisRad == false && (rootIdx > 2 && jointName == "root"))
        if (jointName == "root" && this->AMCisRad == false && rootIdx > 2)
          buffer = glm::radians(buffer);
        else if (jointName != "root" && this->AMCisRad == false)
          buffer = glm::radians(buffer);
        motion.push_back(buffer);
        rootIdx++;
      }

      std::map<std::string, Joint>::iterator joint =
          this->joints.find(jointName);
      // tx, ty, tz, rx, ry, rz 순서
      int ck[6] = {-1, -1, -1, -1, -1, -1};
      for (int i = 0; i < joint->second.dof.size(); i++) {
        if (joint->second.dof[i] == "tx")
          ck[0] = i;
        else if (joint->second.dof[i] == "ty")
          ck[1] = i;
        else if (joint->second.dof[i] == "tz")
          ck[2] = i;
        else if (joint->second.dof[i] == "rx")
          ck[3] = i;
        else if (joint->second.dof[i] == "ry")
          ck[4] = i;
        else if (joint->second.dof[i] == "rz")
          ck[5] = i;
      }
      std::vector<float> jointDof(6, 0);
      for (int i = 0; i < 6; i++) {
        if (ck[i] != -1)
          jointDof[i] = motion[ck[i]];
      }

      this->keyFrame.back().motions.insert(std::make_pair(jointName, jointDof));
    }
  }

  file.close();
  return true;
}