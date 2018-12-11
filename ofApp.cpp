#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_seed = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(10);

	if (ofGetFrameNum() % 60 < 45) {
	
		this->noise_seed += ofMap(ofGetFrameNum() % 60, 0, 45, 0.04, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 120;
	int range = 100;
	int radius = 20;
	for (int x = span * 0.5; x < ofGetWidth(); x += span) {

		for (int y = span * 0.5; y < ofGetHeight(); y += span) {

			glm::vec2 center_point;
			int number_of_point = 4;
			for (int i = 0; i < number_of_point; i++) {

				glm::vec2 point = glm::vec2(
					x + ofMap(ofNoise(ofRandom(10000), this->noise_seed), 0, 1, -range * 0.5, range * 0.5),
					y + ofMap(ofNoise(ofRandom(10000), this->noise_seed), 0, 1, -range * 0.5, range * 0.5));

				if (i == 0) {

					ofNoFill();
					ofSetColor(255);
					ofDrawCircle(point, radius);

					center_point = point;
				}
				else {

					ofFill();
					ofColor color;
					color.setHsb((int)(ofRandom(255) + this->noise_seed * ofRandom(100, 200)) % 255, 200, 255);
					ofSetColor(color);
					ofDrawCircle(point, radius * 0.3);

					float angle = std::atan2(point.y - center_point.y, point.x - center_point.x);
					glm::vec2 line_point = center_point + glm::vec2(radius * cos(angle), radius * sin(angle));
					
					ofDrawLine(line_point, point);

					float rad_span = PI / 3;
					ofBeginShape();
					for (float rad = angle - rad_span; rad <= angle + rad_span; rad += PI / 60) {

						ofVertex(center_point + glm::vec2(radius * 0.8 * cos(rad), radius * 0.8 * sin(rad)));
					}
					for (float rad = angle + rad_span; rad >= angle - rad_span; rad -= PI / 60) {

						ofVertex(center_point + glm::vec2(radius * 0.3 * cos(rad), radius * 0.3 * sin(rad)));
					}
					ofEndShape(true);
				}
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}