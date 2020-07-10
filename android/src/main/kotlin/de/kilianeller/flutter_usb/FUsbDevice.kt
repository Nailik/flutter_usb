package de.kilianeller.flutter_usb

import android.hardware.usb.UsbDeviceConnection
import android.hardware.usb.UsbEndpoint
import java.nio.ByteBuffer
import java.nio.ByteOrder

class FUsbDevice(private val epIn: UsbEndpoint, private val epOut: UsbEndpoint, private val connection: UsbDeviceConnection) {

    private val sendTimeout = 30000
    private val receiveTimeout = 30000
    private var transferred = 0
    private var onResponseCallback: ((result: Response) -> Unit)? = null
    private var onTransferredCallback: (() -> Unit)? = null

    fun sendData(inData: Int, data: ByteArray) {
        //TODO in thread?
        transferred = connection.bulkTransfer(epOut, data, data.size, sendTimeout)
        //transferred < 0 is failure
        if(inData > 0) { //only wait for data if user wants
            waitForResponse(inData)
        }
    }

    private fun waitForResponse(inData: Int) {
        var response = false
        val inb = ByteBuffer.allocate(inData).order(ByteOrder.LITTLE_ENDIAN)
        var res = 0
        while (!response) {
            inb.position(0)
            while (res == 0) {
                res = connection.bulkTransfer(epIn, inb.array(), inData, receiveTimeout)
            }
            if (res >= 1) {
                response = true
            }
        }
        onResponseCallback?.invoke(Response("ok", transferred, inb.array().copyOf(res)));
    }

    fun onResponse(callback: (result: Response) -> Unit = {}): FUsbDevice {
        onResponseCallback = callback
        return this
    }

    fun onTransferred(callback: () -> Unit = {}): FUsbDevice {
        onTransferredCallback = callback
        return this
    }

}