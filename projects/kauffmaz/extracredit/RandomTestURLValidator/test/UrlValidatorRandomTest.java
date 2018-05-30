
/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import junit.framework.TestCase;
import java.util.Random;

public class UrlValidatorRandomTest extends TestCase {


	public UrlValidatorRandomTest(String testName) {
		super(testName);
	}


	public void randomTest() {
		Random rand = new Random();
		UrlValidator urlVal = new UrlValidator();
		int failedtests = 0 , passedtests = 0;
		int totaltests;
		

		String[] schemeArr = { "http://", "ftp://", "h3t://", "", "http:/", "http:", "http/", "://" }; // indices 3-7 invalid
																										

		String[] authArr = { "www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com",//indices 6-17 invalid
				"256.256.256.256", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a", "go.1aa", "aaa.",
				".aaa", "aaa", "" };

		String[] portArr = { ":80", ":65535", ":0", "", ":-1", ":65a" }; //indices 5-7 invalid

		String[] pathArr = { "/test1", "/t123", "/$23", "/test1/", "", "/test1/file", "/..", "/../", "/..//file", //indices 6-9 invalid
				"/test1//file" };

		for (int i = 0; i < 1000000; i++) {
			boolean expected = true;
			
			//randomly pick an index from the array pools
			int schemeNum = rand.nextInt(8);
			int authNum = rand.nextInt(18);
			int portNum = rand.nextInt(6);
			int pathNum = rand.nextInt(10);
			
			//any of these will cause the url to be invalid
			if(schemeNum > 1 || authNum > 5 || portNum > 3 || pathNum > 5) {
				expected = false;
			}
			
			//pick the parts of the url with the
			String randUrlScheme = schemeArr[schemeNum];
			String randAuth = authArr[authNum];
			String randPort = portArr[portNum];
			String randPath = pathArr[pathNum];
			
			//build the url
			String url = randUrlScheme + randAuth + randPort + randPath;
			
			//test the function
			boolean actual = urlVal.isValid(url);
			
			//assert the result
			boolean result = assertTrue(expected, actual);
			
			if(result == false) {
				if(expected == true) {
					System.out.println("TEST FAILED FOR URL:"+ url + " URL should be valid, but returned invalid");
				}
				else {
					System.out.println("TEST FAILED FOR URL:"+ url + " URL should be invalid, but returned valid");
				}
				failedtests++;
			}
			else {
				passedtests++;
			}
		}
		totaltests = failedtests + passedtests;
		System.out.println("RESULTS:");
		System.out.println("Total tests = " + totaltests);
		System.out.println("Passed tests = " + passedtests);
		System.out.println("Failed tests = " + failedtests);
	}

	public boolean assertTrue(boolean expected, boolean actual) {
		return expected == actual;
	}



	public static void main(String[] argv) {

		UrlValidatorRandomTest fct = new UrlValidatorRandomTest("url test");
		// fct.setUp();
		// fct.testIsValid();
		// fct.testIsValidScheme();
		fct.randomTest();
	}


}