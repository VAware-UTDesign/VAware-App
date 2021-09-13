import * as React from 'react';
import { Alert, Button, StyleSheet } from 'react-native';

import EditScreenInfo from '../components/EditScreenInfo';
import { Text, View } from '../components/Themed';
import { RootTabScreenProps } from '../types';

export default function TabOneScreen({ navigation }: RootTabScreenProps<'TabOne'>) {
  return (
    <View style={styles.container}>
        <Text style={styles.title}>VAWARE</Text>
        <View style={styles.buttonContainer}>
          <Button
            title="Connect"
            color="white"
            onPress={() => Alert.alert('Simple Button pressed')}
          />
        </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container :{
    backgroundColor: '#0078DC',
    flex: 1,
    justifyContent: 'center',
  },
  title: {
    fontSize: 60,
    textAlign: 'center',
  },
  button: {
    color: 'grey',
  },
  buttonContainer: {
    width: '60%',
    backgroundColor: 'grey',
    borderRadius: 15,
    color: 'white',
    alignItems: 'center',
  }
});
