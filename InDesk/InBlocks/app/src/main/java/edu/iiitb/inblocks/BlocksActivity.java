package edu.iiitb.inblocks;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.webkit.JavascriptInterface;
import android.webkit.WebView;
import android.widget.Toast;


public class BlocksActivity extends ActionBarActivity {

    private final String TAG = BlocksActivity.class.getSimpleName();

    // Intent request codes
    private static final int REQUEST_CONNECT_DEVICE_SECURE = 1;
    private static final int REQUEST_ENABLE_BT = 3;

    // Message types sent from the BluetoothService Handler
    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;

    // Key names received from the BluetoothService Handler
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";

    // Local Bluetooth adapter
    private BluetoothAdapter mBluetoothAdapter = null;
    // Member object for the chat services
    private BluetoothService mChatService = null;
    // string buffer for outgoing messages
    private StringBuffer mOutStringBuffer = null;
    // Name of the connected device
    private String mConnectedDeviceName = null;
    // Address of the connected device
    private String mDeviceAddress = null;
    // flag to check real or virtual robot
    private boolean isVirtual = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_blocks);

        // check if device_address is available in the intent
        if ( getIntent() != null && getIntent().hasExtra("device_address")) {

            mDeviceAddress = getIntent().getExtras().getString("device_address");
            Log.i(TAG, mDeviceAddress);
            isVirtual = false;
            // initialise Bluetooth Adapter
            mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
            // turn on bluetooth
            if (!mBluetoothAdapter.isEnabled())
            {
                Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
            }
            else {
                if (mChatService == null)
                    setupChat();
                    connectDevice();
            }

        }

        WebView myWebView = (WebView) findViewById(R.id.webView);
        myWebView.loadUrl("file:///android_asset/index.html");
        myWebView.getSettings().setJavaScriptEnabled(true);
        myWebView.addJavascriptInterface(new WebInterface(this), "Android");

    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(TAG, "onActivityResult " + resultCode);
        switch (requestCode) {
            case REQUEST_ENABLE_BT:
                if (resultCode == Activity.RESULT_OK) {
                    setupChat();
                    connectDevice();
                } else {
                    Log.d(TAG, "BT not enabled");
                    Toast.makeText(this, "Bluetooth was not enabled.", Toast.LENGTH_SHORT).show();
                }
        }
    }

    private void connectDevice() {
        BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(mDeviceAddress);
        mChatService.connect(device, true);
    }

    private void setupChat()
    {
        Log.d(TAG, "setupChat()");
        mChatService = new BluetoothService(this, mHandler);
        mOutStringBuffer = new StringBuffer("");
    }

    /**
     * The Handler that gets information back from the BluetoothService
     */
    private final Handler mHandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MESSAGE_STATE_CHANGE:
                    Log.i(TAG, "MESSAGE_STATE_CHANGE: " + msg.arg1);
                    switch (msg.arg1) {
                        case BluetoothService.STATE_CONNECTED:
                            break;
                        case BluetoothService.STATE_CONNECTING:
                            break;
                        case BluetoothService.STATE_LISTEN:
                        case BluetoothService.STATE_NONE:
                            break;
                    }
                    break;
                case MESSAGE_WRITE:
                    byte[] writeBuf = (byte[]) msg.obj;
                    String writeMessage = new String(writeBuf);
                    break;
                case MESSAGE_READ:
                    byte[] readBuf = (byte[]) msg.obj;
                    String readMessage = new String(readBuf, 0, msg.arg1);
                    break;
                case MESSAGE_DEVICE_NAME:
                    mConnectedDeviceName = msg.getData().getString(DEVICE_NAME);
                    Toast.makeText(getApplicationContext(), "Connected to " + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
                    Log.i(TAG, "Connected to " + mConnectedDeviceName);
                    break;
                case MESSAGE_TOAST:
                    Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),
                            Toast.LENGTH_SHORT).show();
                    break;
            }
        }
    };

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.blocks, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public class WebInterface
    {
        Context mContext;
        int mCommand = 0;

        private final String TAG = WebInterface.class.getSimpleName();

        /** Instantiate the interface and set the context */
        WebInterface(Context c) {
            mContext = c;
        }

        @JavascriptInterface
        public void forward(String time, String distance) {
            String msg = "FORWARD " + time + " " + distance + "\n";
//            Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
            mChatService.write(msg.getBytes());
        }

        @JavascriptInterface
        public void backward(String time,String distance) {
            String msg = "BACKWARD " + time + " " + distance + "\n";
//            Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
            mChatService.write(msg.getBytes());
        }

        @JavascriptInterface
        public void left(String angle) {
            String msg = "LEFT " + angle + " " + "?" + "\n";
//            Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
            mChatService.write(msg.getBytes());
        }

        @JavascriptInterface
        public void right(String angle) {
            String msg = "RIGHT " + angle + " " + "?" + "\n";
//            Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
            mChatService.write(msg.getBytes());
        }

        @JavascriptInterface
        public void stopWheels() {
            String msg = "STOP " + "?" + " " + "?" + "\n";
//            Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
            mChatService.write(msg.getBytes());
        }


        @JavascriptInterface
        public void play(String note, String beat) {
            String msg = "PLAY " + note + " " + beat + "\n";
//            Toast.makeText(mContext, msg, Toast.LENGTH_SHORT).show();
            mChatService.write(msg.getBytes());
        }

    }
}
