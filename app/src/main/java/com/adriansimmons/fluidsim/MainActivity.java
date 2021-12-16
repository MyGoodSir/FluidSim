package com.adriansimmons.fluidsim;


import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.TextView;


public class MainActivity extends Activity implements SensorEventListener {
    FluidSimView view;
    private SensorManager mSensorManager;
    private Sensor mSensorAccelerometer;
    private Sensor mSensorMagnetometer;
    private float[] mAccelerometerData = new float[3];
    private float[] mMagnetometerData = new float[3];

    @Override protected void onCreate (Bundle bun){
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        super.onCreate(bun);
        view = new FluidSimView(getApplication());
        setContentView(view);
        mSensorManager = (SensorManager) getSystemService(
                Context.SENSOR_SERVICE);
        mSensorAccelerometer = mSensorManager.getDefaultSensor(
                Sensor.TYPE_ACCELEROMETER);
        mSensorMagnetometer = mSensorManager.getDefaultSensor(
                Sensor.TYPE_MAGNETIC_FIELD);
    }
    @Override
    public void onSensorChanged (SensorEvent sensorEvent){
        int sensorType = sensorEvent.sensor.getType();
        switch (sensorType) {
            case Sensor.TYPE_ACCELEROMETER:
                mAccelerometerData = sensorEvent.values.clone();
                break;
            case Sensor.TYPE_MAGNETIC_FIELD:
                mMagnetometerData = sensorEvent.values.clone();
                break;
            default:
                return;
        }
        float[] rotationMatrix = new float[9];
        boolean rotationOK = SensorManager.getRotationMatrix(rotationMatrix,
                null, mAccelerometerData, mMagnetometerData);
        float orientationValues[] = new float[3];
        if (rotationOK) {
            SensorManager.getOrientation(rotationMatrix, orientationValues);
        }
        float az = (orientationValues[0]); //z axis
        FluidSimNativeLib.rotate(az);
    }

    @Override protected void onPause () {
        super.onPause();
        view.onPause();
        mSensorManager.unregisterListener(this);
    }
    @Override protected void onResume () {
        super.onResume();
        view.onResume();
        mSensorManager.registerListener(this,mSensorAccelerometer,SensorManager.SENSOR_DELAY_NORMAL);
        mSensorManager.registerListener(this,mSensorMagnetometer,SensorManager.SENSOR_DELAY_NORMAL);
    }
    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {
    }

}