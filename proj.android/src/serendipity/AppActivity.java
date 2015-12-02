package serendipity;

import android.widget.Toast;
import android.content.res.Configuration;
import android.util.Log;
import java.lang.Exception;

import org.cocos2dx.lib.Cocos2dxActivity;

public class AppActivity extends Cocos2dxActivity {
    private static final String TAG = "[serendipity.AppActivity]";

    public static native void screenOrientationChanged(int orientation);

    public AppActivity()
    {
        Log.v(TAG, "serendipity.AppActivity instantiated successfully!");
    }

    public boolean release()
    {
        try {
            Log.v(TAG, "serendipity.AppActivity released successfully!");
        }

        catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        return true;
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        if (newConfig.orientation == Configuration.ORIENTATION_PORTRAIT) {
            AppActivity.screenOrientationChanged(1);
        } else if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
            AppActivity.screenOrientationChanged(2);
        } else {
            AppActivity.screenOrientationChanged(0);
        }
    }

    public void debug(final CharSequence log)
    {
        try {
            Log.v(TAG, "debug");
            
            this.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast toast = Toast.makeText(AppActivity.this, log, Toast.LENGTH_SHORT);
                    toast.show();
                }
            });
        }

        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
