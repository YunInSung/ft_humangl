#ifndef __SKELETON_H__
#define __SKELETON_H__

#include "common.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#define FRAMERATE 60.f

#define EULER_XYZ 0
#define EULER_XZY 1
#define EULER_YXZ 2
#define EULER_YZX 3
#define EULER_ZXY 4
#define EULER_ZYX 5

struct Joint {
  uint32_t index;
  std::string name;
  glm::vec3 position;
  glm::vec3 axis;
  int eulerOrder;

  glm::mat4 _C;
  glm::mat4 _Cinv;
  // glm::mat4 _ROT; // = CinvMC (C * M * Cinv)
  // glm::vec3 _B;
  // // L = CinvMCB

  std::vector<std::string> dof;
  std::vector<glm::vec2> limits;
};

struct KeyFrame {
  uint32_t sequence;
  float time;
  std::map<std::string, std::vector<float>> motions;
};

CLASS_PTR(Skeleton)
class Skeleton {
  private:
    Skeleton() {}
    std::string version;
    std::string name;
    std::string documentation;
    float mass_;
    float globalLengthMultiplier_;
    bool isDegree_;

    std::map<std::string, Joint> joints;
    std::map<std::string, std::vector<std::string>> hierarchy; // 부모 자식 관계도
    std::map<std::string, std::vector<uint32_t>> hierarchyOfGrandChild;
    void recursiveHierarchy(std::string bone);
    void recursiveMultiplyMat(KeyFrame& first, KeyFrame& second, std::string bone, float deltaTime);
    glm::mat4 makeMotionMat(KeyFrame& first, KeyFrame& second, std::string bone, float deltaTime);

    bool setASF(std::string const &filename);
    bool setUnit(std::fstream &file);
    bool setRoot(std::fstream &file);
    bool setRootOrder(std::fstream &file, Joint &root);
    bool setBoneData(std::fstream &file);
    bool setBoneDataDof(std::fstream &file, Joint &joint);
    bool setBoneDataLimits(std::fstream &file, Joint &joint);
    bool setHierarchy(std::fstream &file);

    std::string AMC_Filename;
    bool isSpecified;
    bool AMCisRad;
    std::vector<KeyFrame> keyFrame;

    bool setAMC(std::string const &filename);

    std::vector<Joint> retChildren(const std::string& parentName);
    std::vector<glm::mat4> transforms;
  public:
    ~Skeleton() {}
    static SkeletonUPtr Load(const std::string& ASFpath, const std::string& AMCpath);

    std::unique_ptr<float[]> getVBO();
    int getJointsSize() const;
    std::vector<glm::mat4> getTransMats(float& nowTime);
    uint32_t getVBOsize();
};

static void skipWhiteSpace(std::fstream &file);
static glm::mat4 eulerRotation(float x, float y, float z, int order);
static std::string peekWord(std::fstream &file);
static std::string peekLine(std::fstream &file);
static std::string trim(std::string &str);
static uint32_t eulerOrder (std::vector<std::string>);

#endif