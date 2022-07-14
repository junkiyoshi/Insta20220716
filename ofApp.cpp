#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	vector<glm::vec3> location_list;
	vector<float> min_distance_list;
	vector<vector<int>> pair_list;

	for (int i = 0; i < 2000; i++) {

		auto R = 300;
		auto r = ofRandom(30, 80);
		auto u = ofRandom(360) + ofGetFrameNum() * ofRandom(0.25, 1.0) * (ofRandom(1) < 1 ? 1 : -1);
		auto v = ofRandom(360) + ofGetFrameNum() * ofRandom(0.25, 1.0) * (ofRandom(1) < 1 ? 1 : -1);

		location_list.push_back(this->make_point(R, r, u, v));
		min_distance_list.push_back(20);
		vector<int> pair;
		pair_list.push_back(pair);
	}

	this->mesh.clear();
	for (int i = 0; i < location_list.size(); i++) {

		for (int k = 0; k < location_list.size(); k++) {

			if (i == k) { continue; }

			auto distance = glm::distance(location_list[i], location_list[k]);

			if (distance < 20) {

				pair_list[i].push_back(k);
				if (min_distance_list[i] > distance) {

					min_distance_list[i] = distance;
				}
			}
		}
	}

	this->mesh.addVertices(location_list);
	for (int i = 0; i < location_list.size(); i++) {

		this->mesh.addColor(ofColor(255, ofMap(min_distance_list[i], 0, 20, 255, 0)));
		for (int k = 0; k < pair_list[i].size(); k++) {

			this->mesh.addIndex(i);
			this->mesh.addIndex(pair_list[i][k]);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	this->mesh.drawWireframe();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 3);
	}
	
	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}