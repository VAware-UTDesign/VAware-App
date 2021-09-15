import React, { useState } from 'react';
import { Pressable, StyleSheet, Image } from 'react-native';

import { Text, View } from '../components/Themed';
import { RootTabScreenProps } from '../types';

export default function ConnectUI({ navigation }: RootTabScreenProps<'TabOne'>) {
  const [modalVisible, setModalVisible] = useState(false);
  return (
    <View style={styles.container}>
      <View style={styles.titleContainer}>
        <Image
          style={styles.image}
          source={require('../assets/images/VA-logo.png')}
        />
      </View>
        <View style={styles.buttonContainer}>
          <Pressable            
            onPress={() => 
              navigation.navigate('Modal')
            }
          >
            <Text style={styles.button}>Connect</Text>
          </Pressable>
        </View>
    </View>
    
  );
}

const styles = StyleSheet.create({
  container :{
    backgroundColor: '#ABD9FF',
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  titleContainer: {
    marginTop: 10,
    backgroundColor: '#ABD9FF',
    marginBottom: 200,
  },
  button: {
    color: 'white',
    textAlign: 'center',
    fontSize: 25,
  },
  buttonContainer: {
    justifyContent: 'center',
    width: 300,
    height: 60,
    backgroundColor: '#A1A3A6',
    borderRadius: 30,
    color: 'white',
  },
  image: {
    width: 200,
    height: 200,
  }
});