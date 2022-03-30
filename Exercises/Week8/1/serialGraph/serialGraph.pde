import processing.serial.*;
import grafica.*;

// Set the sampling rate using this variable, possible values between 65,5kHz and 16Hz:
String sampleRate = "5000";
// Memory depth value must match with the AVR:
static int memoryDepth = 512;

int[] sample;
float voltage;
int cumulativeTime;

// Initial handshake flag:
boolean handshakeComplete = false;

Serial serialPort;

GPlot plot;
GPointsArray points = new GPointsArray();

void setup() {
  // Set window size:
  size(700, 700);

  // List all available serial ports
  printArray(Serial.list());
  // Init the port:
  serialPort = new Serial(this, Serial.list()[0], 115200);

  // Read the serial data to a buffer until a linefeed is received:
  serialPort.bufferUntil('\n');
  
  // Plot setup:
  plot = new GPlot(this);
  plot.setPos(0, 0);
  plot.setDim(600, 600);
  plot.getXAxis().getAxisLabel().setText("Time (microseconds)");
  plot.getYAxis().getAxisLabel().setText("Voltage");
  plot.setPointColor(color(0, 0, 0, 255));
  plot.setPointSize(2);
  plot.addPoint(0, 0);
  
  // Disable automatic screen refresh:
  noLoop();
}

// Serial event handler:
void serialEvent(Serial serialPort) {
  String input = serialPort.readStringUntil('\n');

  if(input != null) {
    input = trim(input);
    
    // Initial state after startup, try the handshake routine:
    if (handshakeComplete == false) {
      if (input.equals("handshake")) {
        serialPort.clear();
        handshakeComplete = true;
        serialPort.write(sampleRate);
        println("Handshake complete, sampling rate is " + sampleRate + " Hz");
      }
      
      // Transmit complete from the AVR side, refresh the graph and send a confirmation back when done:
    } else if (input.equals("complete")) {
      redraw();
      serialPort.clear();
      serialPort.write("ready");
      
      // AVR is transmitting the samples from memory:
    } else {
      // Implement a sliding window:
      if(plot.getPointsRef().getNPoints() > memoryDepth) {
        plot.removePoint(0);
      }
      
      // Parse the data packets into samples:
      sample = int(split(input, ','));
      if(sample.length == 2) {
        cumulativeTime += sample[0];
        voltage = map(sample[1], 0, 255, 0, 5);
        plot.addPoint(cumulativeTime, voltage);
      }
    }
  }
}

// Display refresh routine:
void draw() {
  background (0);
  plot.beginDraw();
  plot.drawBackground();
  plot.drawBox();
  plot.drawXAxis();
  plot.drawYAxis();
  plot.drawTitle();
  plot.drawGridLines(GPlot.BOTH);
  plot.drawLines();
  plot.endDraw();
}
