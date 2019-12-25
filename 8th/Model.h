//
//  Header.h
//  fifth
//
//  Created by Zhang Zhuyan on 28/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef MODEL_H
#define MODEL_H

#include <glm.hpp>
#include <gtx/string_cast.hpp>
#include "STB.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include "Animation.h"
#include "JointTransform.h"


using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
void AddBoneData(int boneID, float weight, int vertexID);
glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& aiMat);
const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
struct BoneInfo {
    
    glm::mat4 boneOffset;
    
    glm::mat4 finalTransformation;
    
};

class Model
{
public:
    /*  Model Data */
 
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
    std::map<std::string, int> boneMap;
    std::map<int, BoneInfo> boneInfoMap;
    vector<Animation> animations;
    float animationTime;
     sf::Clock clock;
    int animationIndex=0;
    const aiScene* mscene;
    Assimp::Importer m_Importer;
    //std::vector<glm::mat4> finalTransformation;
    glm::mat4 m_global_inverse_transform;
    glm::vec3 position;
    /*  Functions   */
    // constructor, expects a filepath to a 3D model.
    Model(string const &path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
       // std::cout<<"everything is doing ok"<<std::endl;
       // for(auto& i:boneInfoMap)
           // std::cout<<"index "<<i.first<< "has bone offset"<<glm::to_string(i.second.boneOffset);
    }
    
    // draws the model, and thus all its meshes
    void Draw(Shader shader)
    {
        std::vector<glm::mat4> finalTransformation;
        sf::Time elapsed = clock.getElapsedTime();
        float  sec= elapsed.asSeconds();
        animationTime=std::fmod(sec,animations[animationIndex].getLength());
       std::cout<<"animation time"<<animationTime<<std::endl;
        // this is the problem
       //std::map<std::string,glm::mat4> currentPose=calculateCurrentAnimationPose();
       
        //std::cout<<"the size of current pose map "<<currentPose.size()<<std::endl;
       // std::cout<<mscene->mRootNode->mName.data<<"*****";
        // until now it is ok.
       applyPoseToJoints(animationTime,mscene->mRootNode ,glm::mat4(1.0f));
        
        

        
        for (int j=0;j<boneInfoMap.size();j++){
            
          finalTransformation.push_back(boneInfoMap[j].finalTransformation);
        }
        
        
        //shader.setMatrixArray("finalTransform", finalTransformation.size(),FinalTransformation);
        //std::cout<<" how many meshes? "<<meshes.size()<<std::endl;
        
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "finalTransform"), finalTransformation.size(), GL_FALSE, glm::value_ptr(finalTransformation[0]));
        //glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),15,GL_FALSE, glm::value_ptr(MA[0]));
        
    for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }
    
    
    void doAnimation(int a)
    {
        animationIndex=a;
        animationTime=0;
        
        
    }
 

    
private:
    /*  Functions   */
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    int count=0;
    // *******************************there got some prog=blem
    map<std::string, glm::mat4> interpolatePose(Keyframe previousFrame, Keyframe nextFrame, float progression) {
        map<string, glm::mat4> currentPose;
        for ( const auto &p : previousFrame.getPose() )
        {
            string jointName=p.first;
            JointTransform previousTransform=previousFrame.getPose()[jointName];
            JointTransform nextTransform=nextFrame.getPose()[jointName];
            //std::cout<<jointName;
           std::cout<<"   previous "<<previousTransform;
           //std::cout<<" next "<<glm::to_string(nextTransform.getLocalCombinedMatrix());
            //std::cout<<"progression as percentage is "<<progression<<std::endl;
            
            //until now correct.
            
            JointTransform currentTransform=previousTransform.interpolate(nextTransform,progression);
            currentPose.insert({jointName,currentTransform.getLocalCombinedMatrix()});
            //std::cout<<jointName<<" current pose "<<currentTransform<<std::endl;
            //std::cout<<jointName<<" current pose "<<std::endl;
        }
        return currentPose;
    }
    
   /* void applyPoseToJoints(map<std::string, glm::mat4> currentPose,aiNode* pNode, glm::mat4 parentTransform) {
        // my mistake here, should add const in front, otherwise it wont work.
        // this function will set joint and its children all the final transformation.
       // std::cout<<&pNode<<std::endl;
        //std::cout<<"name is***"<<pNode->mName.data<<"--********";
         // this is the default transformation.
        
        string NodeName=pNode->mName.data;
       // std::cout<<"apply Pose Joints to  "<<NodeName;
    glm::mat4  LocalTransform = aiMatrix4x4ToGlm(pNode->mTransformation);//
    //glm::mat4  LocalTransform(1.0f);
        //std::cout<<"hi"<<std::endl;
       // glm::mat4 currentLocalTransform(1.0f);
        //currentPose.find(NodeName) == currentPose.end()
        if ( currentPose.find(NodeName) == currentPose.end()) {
            
            // not found
            
           
        } else {
        //LocalTransform =LocalTransform*currentPose[NodeName];
            //LocalTransform =LocalTransform*glm::mat4(1.0f);
            // if go the other way:
            // LocalTransform =currentPose[NodeName]*LocalTransform; it will rotate around it's grand father's joint
            //LocalTransform =currentPose[NodeName];
            // found
            //std::cout<<"my node name is   "<<NodeName<<"   "<<glm::to_string(currentPose[NodeName])<<std::endl;
        }
        
   
        
        
        
        glm::mat4 currentTransform = parentTransform*LocalTransform;
        //glm::mat4 currentTransform = parentTransform*LocalTransform;
        
        // not all node got bone.
       // std::cout<<NodeName<<" is the node/bone name "<<std::endl;
        if ( boneMap.find(NodeName) == boneMap.end() ) {
            
            // not found
            
        } else {
            // found  if the node got bone.
            int BoneIndex = boneMap[NodeName];
            //boneInfoMap[BoneIndex].boneOffset  m_global_inverse_transform;
            boneInfoMap[BoneIndex].finalTransformation=m_global_inverse_transform*currentTransform*boneInfoMap[BoneIndex].boneOffset;
           // boneInfoMap[BoneIndex].finalTransformation=glm::mat4(1.0f);
          // std::cout<<NodeName<<" of index "<<BoneIndex<< "is having matrix"<< glm::to_string(boneInfoMap[BoneIndex].finalTransformation)<<std::endl;
        }
        
        //std::cout<<"i have "<<pNode->mNumChildren<<"--";
        for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
            
            applyPoseToJoints(currentPose,pNode->mChildren[i],  currentTransform);
        }
        
    }
    
    */
    
    void applyPoseToJoints(float AnimationTime,aiNode* pNode, glm::mat4 parentTransform) {
    
        
        string NodeName=pNode->mName.data;
        // std::cout<<"apply Pose Joints to  "<<NodeName;
        const aiAnimation* pAnimation=mscene->mAnimations[0];
        glm::mat4  LocalTransform = aiMatrix4x4ToGlm(pNode->mTransformation);//
        const aiNodeAnim* pNodeAnim=FindNodeAnim(pAnimation,NodeName);
        //glm::mat4  LocalTransform(1.0f);
        //std::cout<<"hi"<<std::endl;
        // glm::mat4 currentLocalTransform(1.0f);
        //currentPose.find(NodeName) == currentPose.end()
        if (pNodeAnim) {
            // Interpolate scaling and generate scaling transformation matrix
            aiVector3D Scaling;
            CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
            glm::vec3 scale = glm::vec3(Scaling.x, Scaling.y, Scaling.z);
            glm::mat4 ScalingM = glm::scale(glm::mat4(1.0f), scale);
            
            // Interpolate rotation and generate rotation transformation matrix
            aiQuaternion RotationQ;
            CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
            glm::quat rotation(RotationQ.w,RotationQ.x,RotationQ.y,RotationQ.z);
            glm::mat4 RotationM = glm::mat4_cast(rotation);
            
            // Interpolate translation and generate translation transformation matrix
            aiVector3D Translation;
            CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
            glm::vec3 translation = glm::vec3(Translation.x, Translation.y, Translation.z);
            glm::mat4 TranslationM = glm::translate(glm::mat4(1.0f), translation);
            
            // Combine the above transformations
            LocalTransform = TranslationM * RotationM *ScalingM;
        }

        glm::mat4 currentTransform = parentTransform*LocalTransform;
        
        if ( boneMap.find(NodeName) == boneMap.end() ) {
            
            // not found
            
        } else {
            // found  if the node got bone.
            int BoneIndex = boneMap[NodeName];
            //boneInfoMap[BoneIndex].boneOffset  m_global_inverse_transform;
            boneInfoMap[BoneIndex].finalTransformation=m_global_inverse_transform*currentTransform*boneInfoMap[BoneIndex].boneOffset;
        }
        
        //std::cout<<"i have "<<pNode->mNumChildren<<"--";
        for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
            
            applyPoseToJoints(AnimationTime,pNode->mChildren[i],  currentTransform);
        }
        
    }
    
    
    int getPreviousFrameIndex() {
        int previousFrameindex=0;
        vector<Keyframe> allFrames = animations[animationIndex].getKeyFrame();
        Keyframe previousFrame = allFrames[previousFrameindex];
        Keyframe nextFrame = allFrames[previousFrameindex];
        for (int i = 1; i < allFrames.size(); i++) {
            nextFrame = allFrames[i];
            if (nextFrame.getTimeStamp() > animationTime) {
                previousFrameindex=i-1;
                break;
            }

        }
        return previousFrameindex;
    }
    
    float calculateProgression(Keyframe previousFrame, Keyframe nextFrame) {
        float totalTime = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
        float currentTime = animationTime - previousFrame.getTimeStamp();
        return currentTime / totalTime;
    }
    
    map<std::string, glm::mat4> calculateCurrentAnimationPose()
    {  int previousFameI=getPreviousFrameIndex();
        //std::cout<<"frame index is "<<previousFameI<<std::endl;
        vector<Keyframe> allFrames = animations[animationIndex].getKeyFrame();
        //std::cout<<"how many frames here? "<<allFrames.size()<<std::endl;
        
        
        

        float progression = calculateProgression(allFrames[previousFameI],allFrames[previousFameI+1]);
        /*for (auto& i:allFrames[previousFameI].getPose())
        {
            std::cout<<"from previous frame"<<i.first<<":"<<glm::to_string(i.second.getLocalCombinedMatrix())<<std::endl;
            
        }
        for (auto& i:allFrames[previousFameI+1].getPose())
        {
            std::cout<<"from next frame"<<i.first<<":"<<glm::to_string(i.second.getLocalCombinedMatrix())<<std::endl;
            
        }
        */
        
        
        return interpolatePose(allFrames[previousFameI],allFrames[previousFameI+1],progression);
        
    }
    
   /* std::map<std::string,JointTransform> extractKeyFrame(float time,aiAnimation* pAnim)
    {
      
        
        int numBones=pAnim->mNumChannels;
        std::map<std::string,JointTransform> tempPose;
        for (int i=0;i<numBones;i++){
            aiNodeAnim* temp=pAnim->mChannels[i];
            bool usefulness=false;
            for (int j=0;j<temp->mNumPositionKeys;j++)
            {
                glm::vec3 translation(1.0f);
                glm::vec3 scaling(1.0f);
                glm::quat rotation(1.0f,0.0,0.0,0.0);

                if(std::abs((float)temp->mPositionKeys[j].mTime-time)<0.001)
                {
                   // glm::vec3 translation;
                    translation.x=temp->mPositionKeys[j].mValue.x;
                    translation.y=temp->mPositionKeys[j].mValue.y;
                    translation.z=temp->mPositionKeys[j].mValue.z;
                   // std::cout<<"translation x is "<<translation.x<<std::endl;
                    usefulness=true;
                }
                if(std::abs((float)temp->mRotationKeys[j].mTime-time)<0.001)
                {
                    aiQuaternion aiRotation(temp->mRotationKeys[j].mValue);
            
                    rotation=glm::quat(float(aiRotation.w),float(aiRotation.x),float(aiRotation.y),float(aiRotation.z));
                    //rotation=glm::quat(float(1),float(0),float(0),float(0));
                    std::cout<<"at this time,node name is  "<<temp->mNodeName.data<<"time is "<<time;
                    std::cout<<"rotation w is "<<rotation.w<<std::endl;
                   
                   std::cout<<"airotation x is "<<rotation.x<<std::endl;
                std::cout<<"airotation y is "<<rotation.y<<std::endl;
                    std::cout<<"airotation z is "<<rotation.z<<std::endl;
                    usefulness=true;
                }
                if(std::abs((float)temp->mScalingKeys[j].mTime-time)<0.001)
                {
                    scaling.x=temp->mScalingKeys[j].mValue.x;
                    scaling.y=temp->mScalingKeys[j].mValue.y;
                    scaling.z=temp->mScalingKeys[j].mValue.z;
                    
                    
                   // std::cout<<"at this time, "<<time;
                     //std::cout<<"scaling w is "<<scaling.x<<std::endl;
                    // std::cout<<"rotation w is "<<aiRotation.w<<std::endl;
                    // std::cout<<"airotation x is "<<rotation.x<<std::endl;
                    // std::cout<<"airotation y is "<<rotation.y<<std::endl;
                    usefulness=true;
                }
                
                
                if (usefulness)
                {
                    string boneName=temp->mNodeName.data;
                    JointTransform jointtransform(translation,rotation,scaling);
                    //std::cout<<"after passing x "<<translation.x<<std::endl;
                    //std::cout<<"rotation is "<<rotation.y<<std::endl;
                    tempPose[boneName]=jointtransform;
                    //std::cout<<"at this time,"<<time<<boneName<<"  has keyframe transformation"<<glm::to_string(jointtransform.getLocalCombinedMatrix());
                    break;
                }
            }
        }
        return tempPose;
    }
    */
    unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
        {
            
            if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
                return i;
            }
        }
        
        assert(0);
        return 0;
    }
    
    unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        assert(pNodeAnim->mNumRotationKeys > 0);
        
        for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
                return i;
            }
        }
        
        assert(0);
        return 0;
    }
    
    unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        assert(pNodeAnim->mNumScalingKeys > 0);
        
        for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
                return i;
            }
        }
        
        assert(0);
        return 0;
    }
    
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        if (pNodeAnim->mNumPositionKeys == 1) {
            Out = pNodeAnim->mPositionKeys[0].mValue;
            return;
        }
        
        unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
        unsigned int NextPositionIndex = (PositionIndex + 1);
        assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
        float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
        const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
        aiVector3D Delta = End - Start;
        Out = Start + Factor * Delta;
    }
    
    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        // we need at least two values to interpolate...
        if (pNodeAnim->mNumRotationKeys == 1) {
            Out = pNodeAnim->mRotationKeys[0].mValue;
            return;
        }
        
        unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
        unsigned int NextRotationIndex = (RotationIndex + 1);
        assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
        float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
        //assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
        const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
        aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
        Out = Out.Normalize();
    }
    
    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        if (pNodeAnim->mNumScalingKeys == 1) {
            Out = pNodeAnim->mScalingKeys[0].mValue;
            return;
        }
        
        unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
        unsigned int NextScalingIndex = (ScalingIndex + 1);
        assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
        float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
        float temp=(float)pNodeAnim->mScalingKeys[ScalingIndex].mTime;
        float Factor = (AnimationTime - temp) / DeltaTime;
        std::cout<<"factor is "<<Factor<<std::endl;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        
        const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
        const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
        aiVector3D Delta = End - Start;
        Out = Start + Factor * Delta;
    }
    
    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
    {
        for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
            const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
            
            if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
                return pNodeAnim;
            }
        }
        
        return NULL;
    }
    
    
    void loadModel(string const &path)
    {
        
        mscene = m_Importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors
        //std::cout<<mscene->mRootNode->mName.data<<"*****";
        if(!mscene || mscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !mscene->mRootNode) // if is Not Zero
        {
            cout << "ERROR::ASSIMP:: " << m_Importer.GetErrorString() << endl;
            return;// exit 
        }
        // retrieve the directory path of the filepath
        directory = path.substr(0, path.find_last_of('/'));
        
        
        // process ASSIMP's root node recursively
       // std::cout<<"it has  "<<mscene->mNumAnimations<<" number of animation"<<std::endl;
        processNode(mscene->mRootNode, mscene);
        
        m_global_inverse_transform = aiMatrix4x4ToGlm(mscene->mRootNode->mTransformation);
        m_global_inverse_transform=glm::inverse(m_global_inverse_transform);
        if (mscene->HasAnimations())
        {
            std::cout<<"********************adding animation now"<<std::endl;
           // globalMatrix =aiMatrix4x4ToGlm(mscene->mRootNode->mTransformation);
            //globalMatrix=glm::inverse(globalMatrix);
        vector<Keyframe> tempkeyframes;
        int numofAnimation=mscene->mNumAnimations;
            std::cout<<numofAnimation<<"     ";
        for (int i=0;i<numofAnimation;i++)
        {
            std::set<float> timings;
            aiAnimation* temp=mscene->mAnimations[i];
            int numBones=temp->mNumChannels;
            
            for (int i=0;i<numBones;i++){
                int Numposition=temp->mChannels[i]->mNumPositionKeys;
                for (int j=0;j<Numposition;j++)
                {
                    timings.insert((float)temp->mChannels[i]->mPositionKeys[j].mTime);
                }
                
                int Numrotation=temp->mChannels[i]->mNumRotationKeys;
                for (int k=0;k<Numrotation;k++)
                {
                    timings.insert((float)temp->mChannels[i]->mRotationKeys[k].mTime);
                }
                
            }
            std::cout<<"number of timing is  "<<timings.size()<<std::endl;
            for (std::set<float>::iterator it=timings.begin(); it!=timings.end(); ++it)
            {
                std::cout<<"the timing is "<<*it<<std::endl;
            }
            
            
            /*for (std::set<float>::iterator it=timings.begin(); it!=timings.end(); ++it)
            {
               // Keyframe tempkeyframe(*it,extractKeyFrame(*it,temp));
                //std::cout<<"loading up now *************"<<std::endl;
                *for (auto& i:tempkeyframe.getPose())
                {
                    std::cout<<"from next frame"<<i.first<<":"<<glm::to_string(i.second.getLocalCombinedMatrix())<<std::endl;
                    
                }
            
                //tempkeyframes.push_back(tempkeyframe);
            }
            */
            
            
            
            string name=temp->mName.data;
            float duration=temp->mDuration*temp->mTicksPerSecond;
            std::cout<<"animation duration "<<duration;
            
            Animation animation(duration,name,tempkeyframes);
            animations.push_back(animation);
            
            
        
    }
        }
    }
    
    
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene)
    {
        // process each mesh located at the current node
        //std::cout<<"got "<<node->mNumMeshes;
        
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
     {
         //std::cout<<"********************mesh index is "<<i<<std::endl;
            // the node object only contains indices to index the actual objects in the scene.
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
       // }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
        
    }
    
    Mesh processMesh(aiMesh *mesh, const aiScene *scene)
    {
        // data to fill
        //same mesh means same color and material
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        Material material;
        
        // Walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            //std::cout<<"the position x is "<<vector.x<<std::endl;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
            // texture coordinates
          
            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* aimaterial = scene->mMaterials[mesh->mMaterialIndex];
        //std::cout<<"getting material number "<<mesh->mMaterialIndex<<std::endl;
        aiColor3D color (0.f,0.f,0.f);
        if( AI_SUCCESS == aimaterial->Get(AI_MATKEY_COLOR_AMBIENT, color) )
        {
            //std::cout<<"it is ambient"<<"color is "<<color.b<<","<<color.g<<color.r<<std::endl;
            material.ambient=glm::vec3(color.r,color.g,color.b);
            
        }
        if( AI_SUCCESS == aimaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) )
        {
            //std::cout<<"it is diffuse"<<"color is "<<color.b<<","<<color.g<<color.r<<std::endl;
            material.diffuse=glm::vec3(color.r,color.g,color.b);
        }
        
        if( AI_SUCCESS == aimaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) )
        {
            //std::cout<<"it is specular "<<"color is "<<color.b<<","<<color.g<<std::endl;
            material.specular=glm::vec3(color.r,color.g,color.b);
        }
        
        //Mesh returnMesh(vertices, indices,material);
        
        if (!mesh->HasBones())
        {
            std::cout<<"this mesh has no bone. *******";
        }
        if (mesh->HasBones())
        {
        std::cout<<"this mesh got "<<mesh->mNumBones<<std::endl;
        for (int i = 0 ; i < mesh->mNumBones ; i++) {
            int temp=-1;
            
        string BoneName(mesh->mBones[i]->mName.data);
          //  std::cout<<i<<BoneName<<" is the bone name "<<"count is "<<count<<std::endl;
            
            if(boneMap.find(BoneName) == boneMap.end()){
                // if this is the new bone.
                BoneInfo bi;
                bi.boneOffset=aiMatrix4x4ToGlm(mesh->mBones[i]->mOffsetMatrix);// 
                boneMap[BoneName] = count;  // count is done on global level
                boneInfoMap[count]=bi;
                count++;
               //std::cout<<"bone name is "<<BoneName <<" off set matrix"<<glm::to_string(aiMatrix4x4ToGlm(mesh->mBones[i]->mOffsetMatrix));
                temp=count-1;
            }
            else
            {
                temp=boneMap[BoneName];
                
                
                // i took 3 days to debug this, the bone count act like bone ID , which will never go down.
                // if BoneA and boneB already inside the map, bone index will always be constant, eventhough BoneA might appear again.
                // this else statement cost me 3 days.:(((((((
            }
            
            //std::cout<<i<<BoneName<<" is the bone name"<<std::endl;
                for (uint j = 0 ; j < mesh->mBones[i]->mNumWeights ; j++) {
                   
                float weight  = mesh->mBones[i]->mWeights[j].mWeight;
                    
                int vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
                if (weight <= 0.1) continue;
                    
                   // returnMesh.AddBoneData(count-1,weight,vertexID);
                    //std::cout<<"i am adding  weight "<<weight<<" of bone ID"<<count-1<<"on to vertex ID"<<vertexID<<std::endl;
                    for (GLuint i = 0; i < NUM_BONES_PER_VERTEX; i++) {
                        
                        if (vertices[vertexID].weights[i] == 0.0f)
                        {
                            
                            vertices[vertexID].boneID[i]= temp;
                            
                            vertices[vertexID].weights[i]= weight;
                            //std::cout<<"vertex ID"<<vertexID<<"    "<<i<<"  bone ID "<<temp<<"and weight "<<weight<<std::endl;
                            break;
                            
                        }
                    
                    
                }
            
            }
            
        }
        }
        
        
            return Mesh(vertices, indices,material);
            
    }
        
    
    
    
    
    // this } is for end model class
        
};



glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4 &aiMat)
{
    return {
        aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1,
        aiMat.a2, aiMat.b2, aiMat.c2, aiMat.d2,
        aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3,
        aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4
    };
}

#endif /* Header_h */
