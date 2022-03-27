using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

public class SynchronousSocketListener {
	public static void StartListening( ) {
		byte[] bytes = new Byte[1024];

		IPHostEntry ipHostInfo = Dns.GetHostEntry( Dns.GetHostName() );
		IPAddress ipAddress = ipHostInfo.AddressList[0];
		IPEndPoint localEndPoint = new IPEndPoint( ipAddress, 10100 );

		Socket listener = new Socket( ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp );

		try {
			listener.Bind( localEndPoint );
			listener.Listen( 1 );

			while( true ) {
				Console.WriteLine( "Server active" );
				// Program is suspended while waiting for an incoming connection.  
				Socket handler = listener.Accept();

				Console.WriteLine( "Connection established" );  
				while( true ) {
					string data = null;

					do {
						int bytesRec = handler.Receive( bytes );
						data += Encoding.ASCII.GetString( bytes, 0, bytesRec );
					}  while( data.IndexOf( "\n" ) == -1 );

					byte[] msg = Encoding.ASCII.GetBytes( data );
					
					Console.WriteLine( "Command received: {0}", data );

					handler.Send( msg );
				}

				handler.Shutdown( SocketShutdown.Both );
				handler.Close();
			}

		} catch( Exception e ) {
			Console.WriteLine( e.ToString() );
		}
	}

	public static int Main( String[] args ) {
		StartListening();
		return 0;
	}
}